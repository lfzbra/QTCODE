#include "gamewindow.h"
#include <QPushButton>
#include <QPushButton>
#include <mybutton.h>
#include<QTimer>
#include<QSound> //多媒体模块下的音效，需要在.pro 中加入 QT += multimedia 模块，详见帮助文档
#include<QPainter>
#include<QPainter>
#include "coingame.h"
#include "QLabel"
#include <QMouseEvent>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    backlifebtn= new MyButton(":/coin/youxiback.png");
    backlifebtn->setParent(this);
    backlifebtn->move(900,500);
    connect(backlifebtn,&QPushButton::clicked,this,[=](){
        emit this->GameWindowback();
    });

    QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);
    /*翻金币*/
    CoinGame *coingamewindow = new CoinGame;

    coinbtn = new MyButton(":/coin/jinbitubiao");
    coinbtn->move(450,190);
    coinbtn->setParent(this);
    connect(coinbtn, &MyButton::clicked,this,[=](){
        coinbtn->zoom1();
        coinbtn->zoom2();
        QTimer::singleShot(500,this,[=](){
                    startSound->play();
                    this->hide();
                    coingamewindow->show();
               });

    });

    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华为新魏");
    font.setPointSize(16);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(QString("翻金币"));
    //label->setStyleSheet("QLabel{background:rgba(255,0,0,128);}");
    label->setGeometry(480,235,110,30);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    QLabel *label1=new QLabel;
    label1->setParent(this);
    QFont font1;
    font1.setFamily("华为新魏");
    font1.setPointSize(20);
    //将字体设置到标签控件中
    label1->setFont(font1);
    label1->setText(QString("更多游戏敬请期待..."));
    //label->setStyleSheet("QLabel{background:rgba(255,0,0,128);}");
    label1->setGeometry(400,350,270,30);



    connect(coingamewindow,&CoinGame::CoinGameback,this,[=](){
        coingamewindow->hide();
        this->show();
    });



}


void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter paintercoin(this);
    QPixmap pixcoin;
    pixcoin.load(":/coin/youxibackground.png");
    paintercoin.drawPixmap(0,0,this->width(),this->height(),pixcoin);
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void GameWindow::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(press_x-release_x>50)
    {
        emit this->GameWindowback();
        press_x=0;
        release_x=0;
   }
    if(release_x-press_x>50)
    {

        emit this->GameWindowback();
        press_x=0;
        release_x=0;
    }
}
