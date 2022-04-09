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
#include "games/gamewindow.h"
#include "pictureW/picturewindow.h"
#include <QMouseEvent>

LifeWindow::LifeWindow(QWidget *parent) : QMainWindow(parent)
{
    Backbtn = new MyButton(":/coin/laji.png");
    Backbtn->setParent(this);
    Backbtn->move(900,500);

    connect(Backbtn,&QPushButton::clicked,this,[=](){
        emit this->LifeWindowback();
    });

    QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);
    //報警界面
    BJWindow *BJwindow =new BJWindow;

     MyButton *BJbtn =new MyButton(":/res/baojin.png");
     BJbtn->move(460,90);
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
     Musicbtn->move(130,90);
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
     Videobtn->move(280,90);
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
     Gameobtn->move(130,240);
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

     //相册界面
    PictureWindow *Picturewindow = new PictureWindow;

     MyButton *Picturebtn = new MyButton(":/res/xiangce.png");
     Picturebtn->move(305,240);
     Picturebtn->setParent(this);
     connect(Picturebtn,&MyButton::clicked,this,[=](){
        Picturebtn->zoom1();
        Picturebtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            startSound->play();
            this->hide();
            Picturewindow->show();
        });
     });

     connect(Picturewindow,&PictureWindow::PictureWindowback,this,[=](){
         Picturewindow->hide();
         this->show();
     });
}

void LifeWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/beijin.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

//    //画背景图标
//    QPixmap pix;
//    pix.load(":/res/Title.png");
//    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
//    resPainter.drawPixmap(10,30,pix);


}
void LifeWindow::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void LifeWindow::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(release_x-press_x>50)
    {
         emit this->LifeWindowback();
        press_x=0;
        release_x=0;
    }
}

