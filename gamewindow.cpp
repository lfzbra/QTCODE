#include "gamewindow.h"
#include <QPushButton>
#include <QPushButton>
#include <mybutton.h>
#include<QTimer>
#include<QSound> //多媒体模块下的音效，需要在.pro 中加入 QT += multimedia 模块，详见帮助文档
#include<QPainter>
#include<QPainter>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    QPushButton *back = new QPushButton("back",this);
    back->setGeometry(900,500,100,80);
    connect(back,&QPushButton::clicked,this,[=](){
        emit this->GameWindowback();
    });
}
