#include "coingame.h"
#include "QPushButton"
#include "mybutton.h"
#include <QPainter>
#include <QPixmap>
#include <QSound>
#include "coinchoice.h"
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

CoinGame::CoinGame(QWidget *parent) : QMainWindow(parent)
{
    QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);

    back = new MyButton(":/coin/BackButton.png");
    back->move(900,530);
    back->setParent(this);
    connect(back,&MyButton::clicked,this,[=](){
        emit this->CoinGameback();
    });



      QLabel *label=new QLabel;
      label->setParent(this);
      QFont font;
      font.setFamily("华为新魏");
      font.setPointSize(20);
      //将字体设置到标签控件中
      label->setFont(font);
      label->setText(QString("点击 START 开始游戏"));
      label->setStyleSheet("QLabel{background:rgba(255,0,0,128);}");
      label->setGeometry(50,100,270,30);

    titlebtn = new MyButton(":/coin/Title.png");
    titlebtn->setParent(this);
    titlebtn->move(312,40);


    CoinChoice *coinchoicewindow = new CoinChoice;
    startbtn = new MyButton(":/coin/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(480,250);
    connect(startbtn,&MyButton::clicked,this,[=](){
        startbtn->zoom1();
        startbtn->zoom2();
        QTimer::singleShot(500,this,[=](){
                    startSound->play();
                   this->hide();/*自身隐藏*/
                   coinchoicewindow->show();
               });
    });

    connect(coinchoicewindow,&CoinChoice::CoinChoiceback,this,[=](){
        coinchoicewindow->hide();
        this->show();
    });


}




void CoinGame::paintEvent(QPaintEvent *)
{
    QPainter paintercoin(this);
    QPixmap pixcoin;
    pixcoin.load(":/coin/OtherSceneBg.png");
    paintercoin.drawPixmap(0,0,this->width(),this->height(),pixcoin);
}


void CoinGame::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void CoinGame::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(press_x-release_x>50)
    {
        emit this->CoinGameback();
        press_x=0;
        release_x=0;
   }
    if(release_x-press_x>50)
    {

        emit this->CoinGameback();
        press_x=0;
        release_x=0;
    }
}
