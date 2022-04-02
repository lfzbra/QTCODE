#include "mainwindow.h"
#include <QPushButton>
#include <mybutton.h>
#include<QTimer>
#include<QSound> //多媒体模块下的音效，需要在.pro 中加入 QT += multimedia 模块，详见帮助文档
#include<QPainter>
#include "bjwindow.h"
#include<QPainter>
#include "lifewindow.h"
#include<QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    this->resize(1024, 600);
#endif

       QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);
    //生活按鍵
    MyButton *Lifebtn = new MyButton(":/res/xiong2.png");
    Lifebtn->move(520,370);
    Lifebtn->setParent(this);
    //生活返回
    LifeWindow *next = new LifeWindow;
    connect(next,&LifeWindow::LifeWindowback,this,[=](){
        next->hide();
        this->show();

    });
    //生活界面
    connect(Lifebtn,&MyButton::clicked,this,[=](){
        Lifebtn->zoom1();
        Lifebtn->zoom2();
        QTimer::singleShot(500,this,[=](){
                    startSound->play();
                   this->hide();/*自身隐藏*/
                   next->show();/*生活界面显示*/
               });
    });
    QLabel *lifelabel =new QLabel;
    lifelabel->setParent(this);
    lifelabel->setFixedSize(100,100);
    lifelabel->setText("生活");
    lifelabel->setStyleSheet("QLabel{color:rgba(0,0,0, 255);}");
    lifelabel->move(590,440);
    //lifelabel->setAlignment(Qt::AlignCenter);
     lifelabel->setAttribute(Qt::WA_TransparentForMouseEvents);
//    //测温界面
    CWWindow *CwWin = new CWWindow;

    MyButton *Cwbtn = new MyButton(":/res/xiong1.png");
     Cwbtn->setParent(this);
     Cwbtn->move(330,310);

     connect(Cwbtn,&MyButton::clicked,this,[=](){
         Cwbtn->zoom1();
         Cwbtn->zoom2();
         QTimer::singleShot(500,this,[=](){
                     startSound->play();
                    this->hide();/*自身隐藏*/
                    CwWin->show();/*测温界面显示*/
                });
       }
       );
     connect(CwWin,&CWWindow::CWWindowback,this,[=](){
         CwWin->hide();
         this->show();

     });
     QLabel *Cwlabel =new QLabel;
     Cwlabel->setParent(this);
     Cwlabel->setFixedSize(100,100);
     Cwlabel->setText("测温");
     Cwlabel->setStyleSheet("QLabel{color:rgba(0,0,0, 255);}");
     Cwlabel->move(455,395);
     //lifelabel->setAlignment(Qt::AlignCenter);
      Cwlabel->setAttribute(Qt::WA_TransparentForMouseEvents);


}

MainWindow::~MainWindow()
{

}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/xiongdong.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

