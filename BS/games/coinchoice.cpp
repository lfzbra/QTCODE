#include "coinchoice.h"
#include "QPushButton"
#include <QPainter>
#include <QPixmap>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QSound>
#include "mybutton.h"
#include "playsence.h"
#include <QDebug>
#include <QMouseEvent>

CoinChoice::CoinChoice(QWidget *parent) : QMainWindow(parent)
{
    QSound *mysound=new QSound(":/res/TapButtonSound.wav",this);
    coinchoicebtn = new MyButton(":/coin/BackButton.png");
    coinchoicebtn->move(900,530);
    coinchoicebtn->setParent(this);
    connect(coinchoicebtn,&MyButton::clicked,this,[=](){
        emit this->CoinChoiceback();
    });


    //显示当前关卡数
      QLabel *label=new QLabel;
      label->setParent(this);
      QFont font;
      font.setFamily("华为新魏");
      font.setPointSize(20);
      //将字体设置到标签控件中
      label->setFont(font);
      label->setText(QString("请选择关卡："));
   //   label->setStyleSheet("QLabel{border-radius: 4px;color:rgb(0,199,140);}");
   //   label->setStyleSheet("QLabel{color:rgb(0,199,140);}");
      label->setStyleSheet("QLabel{background:rgba(255,0,0,128);}");
      label->setGeometry(50,50,170,30);
      //label->move(100,500);

    //创建选择关卡的按钮
     for(int i=0;i<20;i++)
     {
         MyButton *btnMenu=new MyButton(":/coin/LevelIcon.png");
         btnMenu->setParent(this);
         btnMenu->move(250+i%4*150,80+i/4*100);

         //监听每个按钮的点击事件
         connect(btnMenu,&MyButton::clicked,[=](){
             mysound->play();
             qDebug()<<QString("您选择的是第 %1 关").arg(i+1);

             // 进入到游戏场景
             this->hide();//将选关场景隐藏
             play =new PlaySence(i+1);
             //设置游戏场景的初始位置
             play->setGeometry(this->geometry());
             play->show();

             connect(play,&PlaySence::PlaySenceback,[=](){
                 this->setGeometry(play->geometry());
                 this->show();
                 delete play;
                 play=NULL;
             });


         });

         //布局并显示按钮
         QLabel * label=new QLabel;
         label->setParent(this);
         label->setFixedSize(btnMenu->width(),btnMenu->height());
         label->setText(QString::number(i+1));
         label->setStyleSheet("QLabel{color:rgba(250, 0, 0, 255);}");
         label->move(250+i%4*150,80+i/4*100);
         label->setAlignment(Qt::AlignCenter);

         //让鼠标穿透label
         label->setAttribute(Qt::WA_TransparentForMouseEvents);



     }


}


void CoinChoice::paintEvent(QPaintEvent *)
{
    QPainter paintercoin(this);
    QPixmap pixcoin;
    pixcoin.load(":/coin/OtherSceneBg.png");
    paintercoin.drawPixmap(0,0,this->width(),this->height(),pixcoin);
}


void CoinChoice::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void CoinChoice::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(press_x-release_x>50)
    {
        emit this->CoinChoiceback();
        press_x=0;
        release_x=0;
   }
    if(release_x-press_x>50)
    {

        emit this->CoinChoiceback();
        press_x=0;
        release_x=0;
    }
}
