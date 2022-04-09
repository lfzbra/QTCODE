#include "mybutton.h"
#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include  <QPixmap>
#include <QBitmap>
#include<QRect>
#include<QIcon>

MyButton::MyButton(QString nom)
{

   this->nompath = nom;
    QPixmap pix;
    bool ret = pix.load(nompath);
    if(!ret)
    {
        qDebug()<<"加载图片失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    //不规则
    this->setStyleSheet("QPushButton{border:none;}");
    this->setFocusPolicy(Qt::NoFocus);
    //设置图标
    this->setIcon(pix);

    //设置图标大小

    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyButton::zoom1()
{
    QPropertyAnimation *amtion = new QPropertyAnimation(this,"geomotry");

    amtion->setDuration(200);

    amtion->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    amtion->setEndValue(QRect(this->x(),this->y()+50,this->width(),this->height()));

    amtion->setEasingCurve(QEasingCurve::OutBounce);

    amtion->start();

}

void MyButton::zoom2()
{

    QPropertyAnimation * amtion = new QPropertyAnimation(this,"geometry");

    amtion->setDuration(200);

    amtion->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    amtion->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    amtion->setEasingCurve(QEasingCurve::OutBounce);

    amtion->start();
}
