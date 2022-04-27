#include "baiduai.h"
#include "tupian.h"
BaiduAI::BaiduAI(QWidget *parent) : QMainWindow(parent)
{

    baidubackbtn = new QPushButton("返回",this);
    baidubackbtn->setGeometry(900,500,100,70);
    connect(baidubackbtn,&QPushButton::clicked,this,[=](){
        emit this->BaiduAIback();
    });

    //图片识别界面
    Tupian *tupianwindow = new Tupian;

    tupianbtn = new QPushButton("图片识别",this);
    tupianbtn->setGeometry(440,180,150,70);
    connect(tupianbtn,&QPushButton::clicked,[=](){
        this->hide();
        tupianwindow->show();
    });

    connect(tupianwindow,&Tupian::Tupianback,this,[=](){
        tupianwindow->hide();
        this->show();
    });

    //拍照识别
    Photography *photographywindow = new Photography;

    photographybtn = new QPushButton("拍照识别",this);
    photographybtn->setGeometry(440,335,150,70);
    connect(photographybtn,&QPushButton::clicked,this,[=](){
        this->hide();
        photographywindow->show();
    });

    connect(photographywindow,&Photography::Photographyback,this,[=](){
        photographywindow->hide();
        this->show();
    });


}

void BaiduAI::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void BaiduAI::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(release_x-press_x>50)
    {
         emit this->BaiduAIback();
        press_x=0;
        release_x=0;
    }
    if(press_x-release_x>50)
    {
         emit this->BaiduAIback();
        press_x=0;
        release_x=0;
    }
}
