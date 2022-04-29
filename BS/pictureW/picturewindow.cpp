#include "picturewindow.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QString>
#include <qstring.h>
#include<QFileDialog>
#include <QMessageBox>

PictureWindow::PictureWindow(QWidget *parent) : QMainWindow(parent)
{
    back = new QPushButton("返回",this);
    //back->setGeometry(900,500,100,80);
    back->setMaximumHeight(70);
    back->setMaximumWidth(200);
    connect(back,&QPushButton::clicked,this,[=](){
        graphicsScene->clear();
        namelabel->setText("未打开文件");
        emit this->PictureWindowback();

    });

    rvboxlayout = new QVBoxLayout(this);
    lvboxlayout = new QVBoxLayout(this);
    hboxlayout = new QHBoxLayout(this);
    rightwidget = new QWidget(this);
    liftwidget =new QWidget(this);
    mainwidget = new QWidget(this);
    namelabel = new QLabel(this);
    openbtn = new QPushButton("打开",this);
    deletebtn = new QPushButton("删除照片",this);
    deleteallbtn = new QPushButton("清空照片",this);

    openbtn->setMaximumHeight(70);
    openbtn->setMaximumWidth(200);
    deletebtn->setMaximumHeight(70);
    deletebtn->setMaximumWidth(200);
    deleteallbtn->setMaximumHeight(70);
    deleteallbtn->setMaximumWidth(200);
    namelabel->setText("未打开文件");



    /* 实例化图形视图对象 */
    graphicsView = new QGraphicsView(this);
    /* 实例化场景对象 */
    graphicsScene = new QGraphicsScene(this);

    /* 在QGraphicsView设置场景 */
    graphicsView->setScene(graphicsScene);

    lvboxlayout->addWidget(namelabel);
    lvboxlayout->addWidget(graphicsView);
    liftwidget->setLayout(lvboxlayout);

    rvboxlayout->addWidget(openbtn);
    rvboxlayout->addWidget(deletebtn);
    rvboxlayout->addWidget(deleteallbtn);
    rvboxlayout->addWidget(back);
    rightwidget->setLayout(rvboxlayout);

    hboxlayout->addWidget(liftwidget);
    hboxlayout->addWidget(rightwidget);

    mainwidget->setLayout(hboxlayout);

    this->setCentralWidget(mainwidget);

    connect(openbtn,&QPushButton::clicked,this,[=](){
        openActionTriggered();
    });
    connect(deletebtn,&QPushButton::clicked,this,[=](){

        Picturedelete();
    });
    connect(deleteallbtn,&QPushButton::clicked,this,[=](){
       if(QMessageBox::Ok == QMessageBox ::question(this,"请求","删除全部图片？",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
       {
           namelabel->setText("未打开文件");
         graphicsScene->clear();
         system("rm /home/root/photo/*.png -rf");
       }
    });
}

void PictureWindow::openActionTriggered()
{

    /*调用系统打开文件窗口，设置窗口标题为“打开文件”，过滤文件名*/
    QString fileName = QFileDialog::getOpenFileName(
                this,tr("打开文件"), "/home/root/photo/",
                tr("Files(*.png *.jpg *.bmp)")
                );
    /* 定义QPixmap对象，指向fileName */
    QPixmap image(fileName);
    /* 将image用scaled来重新设置长宽为graphicsView的长宽，
     * 保持纵横比等
     */

    /* 假若用户没选择文件，则返回 */
    if(image.isNull())
        return;
    image = image.scaled(graphicsView->width(),
                          graphicsView->height(),
                          Qt::KeepAspectRatio,
                          Qt::FastTransformation
                          );
    /* 在添加场景内容前，先清除之前的场景内容 */
    graphicsScene->clear();
    /* 添加场景内容image */
    graphicsScene->addPixmap(image);

    namelabel->setText("文件名："+fileName);
}

void PictureWindow::Picturedelete()
{

    /*调用系统打开文件窗口，设置窗口标题为“打开文件”，过滤文件名*/
    QString fileName1 = QFileDialog::getOpenFileName(
                this,tr("打开文件"), "/home/root/photo/",
                tr("Files(*.png *.jpg *.bmp)")
                );
  
    QString s = "rm -rf "+fileName1;
    char *c ;
    QByteArray ba = s.toLatin1();
    c= ba.data();
    const char* ss = c;
    system(ss);

}


void PictureWindow::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void PictureWindow::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(press_x-release_x>50)
    {
        namelabel->setText("未打开文件");
        graphicsScene->clear();
        emit this->PictureWindowback();
        press_x=0;
        release_x=0;
   }
    if(release_x-press_x>50)
    {

        namelabel->setText("未打开文件");
        graphicsScene->clear();
        emit this->PictureWindowback();
        press_x=0;
        release_x=0;
    }
}

