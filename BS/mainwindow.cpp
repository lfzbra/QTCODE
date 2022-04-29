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
#include <QPaintEvent>
#include<QDateTime>
#include <QProcess>
#include <QTime>
#include <QDebug>


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
    //system("source ./home/root/shell/wifi/alientek_usb_wifi_setup.sh -m station -i lfz -p 12345678 -d wlan0");

#else
    /* 否则则设置主窗体大小为800x480 */
    this->resize(1024, 600);
#endif

    //获取网络时间
    webtime =new webTimeGetter(this);
    webtime->tryGet();
    //时间获取和设置
    //QTime time = QTime::currentTime();
    timer = new QTimer(this);
    lcdnumber = new QLCDNumber(this);
    //QDateTime current_date_time =QDateTime::currentDateTime();
    lcdnumber->setGeometry(412, 150, 200, 50);

    lcdnumber->setDigitCount(8);
    lcdnumber->setSegmentStyle(QLCDNumber::Flat);
    //lcdnumber->display(time.toString("hh:mm:ss"));
    lcdnumber->display(QString::number(endtime[3])+":"+QString::number(endtime[4])+":"+QString::number(endtime[5]));
    lcdnumber->setStyleSheet("color:white;");
    connect(timer, SIGNAL(timeout()), this,SLOT(timerTimeOut()));

    //QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    //QString current_date =current_date_time.toString("yyyy.MM.dd");
    //QString current_date = QString::number(endtime[0])+"."+QString::number(endtime[1])+"."+QString::number(endtime[2]);
    label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华为新魏");
    font.setPointSize(20);
    //将字体设置到标签控件中
    label->setFont(font);
    //label->setText("0.0.0");
    label->setText(QString::number(endtime[0])+"."+QString::number(endtime[1])+"."+QString::number(endtime[2]));
    label->setStyleSheet("color:white;");
    label->setGeometry(20,20,200,50);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    this->setMouseTracking(true);
       QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);
    //生活按鍵
    MyButton *Lifebtn = new MyButton(":/res/xiong2.png");
    Lifebtn->move(520,370);
    Lifebtn->setParent(this);
    //生活返回
    next = new LifeWindow;
    connect(next,&LifeWindow::LifeWindowback,this,[=](){
        next->hide();
        this->show();
        webtime->tryGet();
    });
    //生活界面
    connect(Lifebtn,&MyButton::clicked,this,[=](){
        Lifebtn->zoom1();
        Lifebtn->zoom2();
        QTimer::singleShot(500,this,[=](){
                    startSound->play();
                   this->hide();/*自身隐藏*/
                   next->show();/*生活界面显示*/
                        //timer->stop();
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
    CwWin = new CWWindow;

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
                    //timer->stop();
                });
       }
       );

     connect(CwWin,&CWWindow::CWWindowback,this,[=](){
         CwWin->hide();
         this->show();
        webtime->tryGet();
     });
     QLabel *Cwlabel =new QLabel;
     Cwlabel->setParent(this);
     Cwlabel->setFixedSize(100,100);
     Cwlabel->setText("测温");
     Cwlabel->setStyleSheet("QLabel{color:rgba(0,0,0, 255);}");
     Cwlabel->move(455,395);
     //lifelabel->setAlignment(Qt::AlignCenter);
      Cwlabel->setAttribute(Qt::WA_TransparentForMouseEvents);

      connect(webtime,&webTimeGetter::dateback,this,[=](){
          //endtime[6]=NULL;
          webtime->readingData(endtime);
          timer->start(1000);
          qDebug()<<endtime[0]<<"=="<<endtime[1];
          endtime[3]+=8;
          if(endtime[3]>23) endtime[3]-=23;
          QString minntest;
          QString hourst;
          QString secondst;
          QString monthst;
          QString dayst;
          if(endtime[3]<10)
          {
              hourst = "0"+QString::number(endtime[3]);
          }
          else
          {
              hourst=QString::number(endtime[3]);
          }
          if(endtime[4]<10)
          {
              minntest = "0"+QString::number(endtime[4]);
          }
          else
          {
              minntest=QString::number(endtime[4]);
          }
          if(endtime[5]<10)
          {
              secondst = "0"+QString::number(endtime[5]);
          }
          else
          {
              secondst=QString::number(endtime[5]);
          }
          if(endtime[1]<10)
          {
              monthst = "0"+QString::number(endtime[1]);
          }
          else
          {
              monthst=QString::number(endtime[1]);
          }
          if(endtime[2]<10)
          {
              dayst = "0"+QString::number(endtime[2]);
          }
          else
          {
              dayst=QString::number(endtime[2]);
          }
          label->setText(QString::number(endtime[0])+"."+monthst+"."+dayst);
          lcdnumber->display(hourst+":"+minntest+":"+secondst);

          //systemdate = QString("date -s "+"\""+QString::number(endtime[0])+"-"+monthst+"-"+dayst+" "+hourst+":"+minntest+":"+secondst+"\"");
          systemdate="date -s \"\"";
          systemdate.insert(9,QString::number(endtime[0])+QString("-")+monthst+QString("-")+dayst+QString(" ")+hourst+QString(":")+minntest+QString(":")+secondst);
          char *c ;
          QByteArray ba = systemdate.toLatin1();
          c= ba.data();
          const char* ss1 = c;
          system(ss1);
          qDebug()<<"ss1="<<ss1;
         // system(systemdate);

      });
      QTimer::singleShot(60000,this,[=](){
           webtime->tryGet();
           qDebug()<<"一分钟定时";
      });
    timer->start(1000);
}

MainWindow::~MainWindow()
{

}

void MainWindow::timerTimeOut()
 {
     /* 当定时器计时 1000 毫秒后，刷新 lcd 显示当前系统时间 */
    QTime time = QTime::currentTime();

    //webtime->tryGet();
    /* 设置显示的样式 */
//    lcdnumber->display(time.toString("hh:mm:ss"));
//    QDateTime current_date_time =QDateTime::currentDateTime();
//    QString current_date =current_date_time.toString("yyyy.MM.dd");
//    label->setText(current_date);
    QString minntest;
    QString hourst;
    QString secondst;
    QString monthst;
    QString dayst;
    endtime[5]++;
    if(endtime[5]>59)
    {
        endtime[4]++;
        if(endtime[4]>59)
        {
            endtime[3]++;
            if(endtime[3]>23)
            {
                endtime[2]++;
               endtime[3]=0;
            }
            endtime[4]=0;
        }
        endtime[5]=0;
    }
    if(endtime[3]<10)
    {
        hourst = "0"+QString::number(endtime[3]);
    }
    else
    {
        hourst=QString::number(endtime[3]);
    }
    if(endtime[4]<10)
    {
        minntest = "0"+QString::number(endtime[4]);
    }
    else
    {
        minntest=QString::number(endtime[4]);
    }
    if(endtime[5]<10)
    {
        secondst = "0"+QString::number(endtime[5]);
    }
    else
    {
        secondst=QString::number(endtime[5]);
    }
    if(endtime[1]<10)
    {
        monthst = "0"+QString::number(endtime[1]);
    }
    else
    {
        monthst=QString::number(endtime[1]);
    }
    if(endtime[2]<10)
    {
        dayst = "0"+QString::number(endtime[2]);
    }
    else
    {
        dayst=QString::number(endtime[2]);
    }
    label->setText(QString::number(endtime[0])+"."+monthst+"."+dayst);
    lcdnumber->display(hourst+":"+minntest+":"+secondst);


 }


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/xiongdong.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(press_x-release_x>50)
    {
        this->hide();/*自身隐藏*/
        next->show();/*生活界面显示*/
        press_x=0;
        release_x=0;
   }
    if(release_x-press_x>50)
    {

        CwWin->show();
        this->hide();
        press_x=0;
        release_x=0;
    }
}

