#include "lifewindow.h"
#include <QPushButton>
#include <bjwindow.h>
#include <QPushButton>
#include <mybutton.h>
#include<QTimer>
#include<QSound> //多媒体模块下的音效，需要在.pro 中加入 QT += multimedia 模块，详见帮助文档
#include<QPainter>
#include "bjwindow.h"
#include<QPainter>
#include "musicwindow.h"
#include "videowindow.h"
#include "gamewindow.h"

LifeWindow::LifeWindow(QWidget *parent) : QMainWindow(parent)
{
    QPushButton *Backbtn = new QPushButton("back",this);
    Backbtn->setGeometry(900,480,100,100);

    connect(Backbtn,&QPushButton::clicked,this,[=](){
        emit this->LifeWindowback();
    });

    QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);
    //報警界面
    BJWindow *BJwindow =new BJWindow;

     MyButton *BJbtn =new MyButton(":/res/ll.png");
     BJbtn->move(850,250);
     BJbtn->setParent(this);
     connect(BJbtn,&MyButton::clicked,this,[=](){
         BJbtn->zoom1();
         BJbtn->zoom2();
         QTimer::singleShot(500,this,[=](){
                     startSound->play();
                    this->hide();/*自身隐藏*/
                    BJwindow->show();
                });
     });
     connect(BJwindow,&BJWindow::BJWindowback,this,[=](){
         BJwindow->hide();
         this->show();
     });

     //音乐界面
     MusicWindow *Musicwindow = new MusicWindow;

     MyButton *Musicbtn = new MyButton(":/res/erji.png");
     Musicbtn->move(300,300);
     Musicbtn->setParent(this);
     connect(Musicbtn,&MyButton::clicked,this,[=](){
        Musicbtn->zoom1();
        Musicbtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            startSound->play();
            this->hide();
            Musicwindow->show();
        });
     });

     connect(Musicwindow,&MusicWindow::MCWindowback,this,[=](){
         Musicwindow->hide();
         this->show();
     });

     //视频界面
     VideoWindow *Videowindow = new VideoWindow;

     MyButton *Videobtn = new MyButton(":/res/diansi.png");
     Videobtn->move(500,300);
     Videobtn->setParent(this);
     connect(Videobtn,&MyButton::clicked,this,[=](){
        Videobtn->zoom1();
        Videobtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            startSound->play();
            this->hide();
            Videowindow->show();
        });
     });

     connect(Videowindow,&VideoWindow::VideoWindowback,this,[=](){
         Videowindow->hide();
         this->show();
     });

     //游戏界面
    GameWindow *Gamewindow = new GameWindow;

     MyButton *Gameobtn = new MyButton(":/res/youxi.png");
     Gameobtn->move(700,300);
     Gameobtn->setParent(this);
     connect(Gameobtn,&MyButton::clicked,this,[=](){
        Gameobtn->zoom1();
        Gameobtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            startSound->play();
            this->hide();
            Gamewindow->show();
        });
     });

     connect(Gamewindow,&GameWindow::GameWindowback,this,[=](){
         Gamewindow->hide();
         this->show();
     });
}

void LifeWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/keting.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

//    //画背景图标
//    QPixmap pix;
//    pix.load(":/res/Title.png");
//    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
//    resPainter.drawPixmap(10,30,pix);


}
