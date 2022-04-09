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
#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>

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
         setLedState(0);
         setBeepState(0);
         ledbnl->hide();
         ledbnm->show();
         beepbnl->hide();
         beepbnm->show();
        emit this->BJWindowback();
    });

    ledbnl = new MyButton(":/res/dl.png");
    ledbnl->setParent(this);
    ledbnl->move(300,300);
    ledbnl->hide();

    ledbnm = new MyButton(":/res/dm.png");
    ledbnm->setParent(this);
    ledbnm->move(300,300);
    ledbnm->hide();

    beepbnm = new MyButton(":/res/lm.png");
    beepbnm->setParent(this);
    beepbnm->move(600,300);
    beepbnm->hide();

    beepbnl = new MyButton(":/res/ll.png");
    beepbnl->setParent(this);
    beepbnl->move(600,300);
    beepbnl->hide();

    /* 开发板的LED控制接口 */
    ledfile.setFileName("/sys/devices/platform/leds/leds/sys-led/brightness");

    if (!ledfile.exists())
        /* 设置按钮的初始化文本 */
        emit this->BJWindowback();

    beepfile.setFileName("/sys/devices/platform/leds/leds/beep/brightness");
    if (!beepfile.exists())
        /* 设置按钮的初始化文本 */
      emit this->BJWindowback();
}

void BJWindow::setLedState(int set)
{
    /* 在设置LED状态时先读取 */
    //bool state = getLedState();

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
   // bool state = getBeepState();

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

   // getBeepState();
}


void BJWindow::keyPressEvent(QKeyEvent *event)
{
#if __arm__
    /* 判断按下的按键，也就是板子KEY0按键 */
    if(event->key() == Qt::Key_VolumeDown) {
        int ledflag=0;
         setLedState(ledflag);

        int beepflag=0;
            setBeepState(beepflag);

            ledbnl->hide();
            ledbnm->show();
            beepbnl->hide();
            beepbnm->show();
    }
#else
    /* 判断按下的按键，也就是"↓"方向键 */
    if(event->key() == Qt::Key_Down) {
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
       int ledflag=1;
        setLedState(ledflag);

       int beepflag=1;
           setBeepState(beepflag);

       ledbnl->show();
       ledbnm->hide();
       beepbnl->show();
       beepbnm->hide();
    }
#else
    /* 判断按下的按键，也就是"↓"方向键 */
    if(event->key() == Qt::Key_Down) {
        int ledflag=0;
         setLedState(ledflag);

        int beepflag=0;
            setBeepState(beepflag);
    }
#endif
    /* 保存默认事件 */
   QWidget::keyReleaseEvent(event);
}

void BJWindow::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void BJWindow::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(press_x-release_x>50)
    {
        emit this->BJWindowback();
        press_x=0;
        release_x=0;
   }
    if(release_x-press_x>50)
    {

        emit this->BJWindowback();
        press_x=0;
        release_x=0;
    }
}
