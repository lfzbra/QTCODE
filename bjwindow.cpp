#include "bjwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QEvent>
#include<QWidget>
#include<QKeyEvent>
#include<QThread>
#include<QLabel>
#include <QPushButton>

BJWindow::BJWindow(QWidget *parent) : QMainWindow(parent)
{
    /* 获取屏幕的分辨率，Qt官方建议使用这
     * 种方法获取屏幕分辨率，防上多屏设备导致对应不上
     * 注意，这是获取整个桌面系统的分辨率
     */
    QList <QScreen *> list_screen =  QGuiApplication::screens();

    /* 如果是ARM平台，直接设置大小为屏幕的大小 */
#if __arm__
    /* 重设大小 */
    this->resize(list_screen.at(0)->geometry().width(),
                 list_screen.at(0)->geometry().height());
    /* 默认是出厂系统的LED心跳的触发方式,想要控制LED，
     * 需要改变LED的触发方式，改为none，即无 */
    system("echo none > /sys/class/leds/sys-led/trigger");
#else
    /* 否则则设置主窗体大小为800x480 */
    this->resize(800, 480);
#endif
    QPushButton *back=new QPushButton("返回",this);
    back->setGeometry(this->width()-130,this->height()-100,100,80);
    connect(back,&QPushButton::clicked,this,[=](){
        emit this->BJWindowback();
    });

    Ledbtn=new QPushButton(this);
    Beepbtn = new QPushButton(this);

    Ledbtn->setMinimumSize(200, 50);
    Ledbtn->setGeometry(200,200,200,50);

    Beepbtn->setMinimumSize(200, 50);
    Beepbtn->setGeometry(500,200,200,50);

    /* 开发板的LED控制接口 */
    ledfile.setFileName("/sys/devices/platform/leds/leds/sys-led/brightness");

    if (!ledfile.exists())
        /* 设置按钮的初始化文本 */
        Ledbtn->setText("未获取到LED设备！");
    /* 获取LED的状态 */
    getLedState();

    /* 信号槽连接 */
    connect(Ledbtn, SIGNAL(clicked()),
            this, SLOT(ledButtonClicked()));
     /*开发板打BEEP控制接*/
    beepfile.setFileName("/sys/devices/platform/leds/leds/beep/brightness");
    if (!beepfile.exists())
        /* 设置按钮的初始化文本 */
       Beepbtn->setText("未获取到beep设备！");
    /* 获取LED的状态 */
    getBeepState();
    connect(Beepbtn, SIGNAL(clicked()),
            this, SLOT(beepButtonClicked()));

    /* 标签实例化 */
    Keybtn = new QPushButton(this);
    Keybtn->setMinimumSize(200, 50);
    Keybtn->setGeometry(500,100,200,50);
    /* 设置默认文本 */
#if __arm__
    Keybtn->setText("VolumeDown松开状态");
#else
    Keybtn->setText("Down按键松开");
#endif

    /* 设置对齐方式 */
    //Keybtn->setAlignment(Qt::AlignCenter);

    /* 居中显示 */
  //  setCentralWidget(label);
}

void BJWindow::setLedState(int set)
{
    /* 在设置LED状态时先读取 */
    bool state = getLedState();

    /* 如果文件不存在，则返回 */
    if (!ledfile.exists())
        return;

    if(!ledfile.open(QIODevice::ReadWrite))
        qDebug()<<ledfile.errorString();

   QByteArray buf[2] = {"0", "1"};


   /* 写0或1 */
   if (set)
       ledfile.write("1");
   else
       ledfile.write("0");

    /* 关闭文件 */
    ledfile.close();

    /*重新获取LED的状态 */
    getLedState();
}

bool BJWindow::getLedState()
{
    /* 如果文件不存在，则返回 */
      if (!ledfile.exists())
          return false;

      if(!ledfile.open(QIODevice::ReadWrite))
          qDebug()<<ledfile.errorString();

      QTextStream in(&ledfile);

      /* 读取文件所有数据 */
      QString buf = in.readLine();

      /* 打印出读出的值 */
      qDebug()<<"buf: "<<buf<<endl;
      ledfile.close();
      if (buf == "1") {
         Ledbtn->setText("LED点亮");
          return true;
      } else {
          Ledbtn->setText("LED熄灭");
          return false;
      }
}

void BJWindow::ledButtonClicked()
{
    /* 设置LED的状态 */
   // setLedState();
}

void BJWindow::beepButtonClicked()
{
    /* 设置beep的状态 */
    //setBeepState();
}

void BJWindow::setBeepState(int set)
{
    /* 在设置BEEP状态时先读取 */
    bool state = getBeepState();

    /* 如果文件不存在，则返回 */
    if (!beepfile.exists())
        return;

    if(!beepfile.open(QIODevice::ReadWrite))
        qDebug()<<beepfile.errorString();

    QByteArray buf[2] = {"0", "1"};

    if (set)
        beepfile.write(buf[1]);
    else
        beepfile.write(buf[0]);

    beepfile.close();

    getBeepState();
}

bool BJWindow::getBeepState()
{
    /* 如果文件不存在，则返回 */
    if (!beepfile.exists())
        return false;

    if(!beepfile.open(QIODevice::ReadWrite))
        qDebug()<<beepfile.errorString();

    QTextStream in(&beepfile);

    /* 读取文件所有数据 */
    QString buf = in.readLine();

    /* 打印出读出的值 */
    qDebug()<<"buf: "<<buf<<endl;
    beepfile.close();
    if (buf == "1") {
        Beepbtn->setText("BEEP开");
        return true;
    } else {
        Beepbtn->setText("BEEP关");
        return false;
    }
}

void BJWindow::keyPressEvent(QKeyEvent *event)
{
#if __arm__
    /* 判断按下的按键，也就是板子KEY0按键 */
    if(event->key() == Qt::Key_VolumeDown) {
        /* 设置label的文本 */
        Keybtn->setText("VolumeDown按键按下");
        //QThread::msleep(500);
        int ledflag=0;
         setLedState(ledflag);

        int beepflag=0;
            setBeepState(beepflag);
    }
#else
    /* 判断按下的按键，也就是"↓"方向键 */
    if(event->key() == Qt::Key_Down) {
        /* 设置label的文本 */
        Keybtn->setText("Down按键按下");
        int ledflag=1;
         setLedState(ledflag);

        int beepflag=1;
            setBeepState(beepflag);
    }

#endif
    /* 保存默认事件 */
    //QWidget::keyPressEvent(event);
}

void BJWindow::keyReleaseEvent(QKeyEvent *event)
{
#if __arm__
    /* 判断松开的按键，也就是板子KEY0按键 */
    if(event->key() == Qt::Key_VolumeDown) {
        /* 设置label的文本 */
       Keybtn->setText("VolumeDown按键松开");
       int ledflag=0;
        setLedState(ledflag);

       int beepflag=0;
           setBeepState(beepflag);
    }
#else
    /* 判断按下的按键，也就是"↓"方向键 */
    if(event->key() == Qt::Key_Down) {
        /* 设置label的文本 */
        Keybtn->setText("Down按键松开");
        int ledflag=0;
         setLedState(ledflag);

        int beepflag=0;
            setBeepState(beepflag);
    }
#endif
    /* 保存默认事件 */
   // QWidget::keyReleaseEvent(event);
}
