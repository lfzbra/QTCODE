#include "musicwindow.h"
#include <QPushButton>

MusicWindow::MusicWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setGeometry(0, 0, 1024, 600);
    QPushButton *MCbtn =new QPushButton("返回",this);
    MCbtn->setGeometry(900, 500, 100, 70);

    connect(MCbtn,&QPushButton::clicked,this,[=](){
        emit this->MCWindowback();
    });
}
