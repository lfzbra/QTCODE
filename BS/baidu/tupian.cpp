#include "tupian.h"
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsView>

Tupian::Tupian(QWidget *parent) : QMainWindow(parent)
{
    layoutInit();

    //tupianbackbtn->setGeometry(900,500,100,70);
    connect(tupianbackbtn,&QPushButton::clicked,this,[=](){
        emit this->Tupianback();
    });

    connect(openbtn,&QPushButton::clicked,this,[=](){
         openfile();
    });

    connect(startbtn,&QPushButton::clicked,this,[=](){
        startread();
    });
    connect(plantbtn,&QPushButton::clicked,this,[=](){
        ocr->readyToDetection(fileName,false);
    });

    connect(ocr, SIGNAL(ocrReadyData(QString)), this, SLOT(disPlaylprResult(QString)));
    //connect(ocr,&Ocr::ocrReadyData(QString),this,disPlaylprResult(QString));
}


void Tupian::layoutInit()
{
    /* 实例化图形视图对象 */
    graphicsView = new QGraphicsView(this);
    /* 实例化场景对象 */
    graphicsScene = new QGraphicsScene(this);
    /* 在QGraphicsView设置场景 */
    graphicsView->setScene(graphicsScene);

    ocr = new Ocr(this);
    tupianbackbtn = new QPushButton("返回",this);
    openbtn = new QPushButton("打开",this);
    startbtn = new QPushButton("动物识别",this);
    tutitle = new QLabel(this);
    tulabel = new QLabel(this);
    rvboxlayout = new QVBoxLayout(this);
    lvboxlayout = new QVBoxLayout(this);
    hboxlayout = new QHBoxLayout(this);
    rwidget = new QWidget(this);
    lwidget = new QWidget(this);
    mainwidget= new QWidget(this);
    plantbtn = new QPushButton("植物识别",this);


    tupianbackbtn->setMaximumSize(100,70);
    openbtn->setMaximumSize(100,70);
    startbtn->setMaximumSize(100,70);
    plantbtn->setMaximumSize(100,70);
    tutitle->setMinimumSize(500,50);
    //tulabel->setMinimumSize(800,500);
    tulabel->setScaledContents(true);

    lvboxlayout->addWidget(tutitle);
    lvboxlayout->addWidget(graphicsView);
    rvboxlayout->addWidget(openbtn);
    rvboxlayout->addWidget(startbtn);
    rvboxlayout->addWidget(plantbtn);
    rvboxlayout->addWidget(tupianbackbtn);

    rwidget->setLayout(rvboxlayout);
    lwidget->setLayout(lvboxlayout);
    hboxlayout->addWidget(lwidget);
    hboxlayout->addWidget(rwidget);

    mainwidget->setLayout(hboxlayout);
    this->setCentralWidget(mainwidget);
    //fileName = new QString(this);



}

void Tupian::openfile()
{
    /*调用系统打开文件窗口，设置窗口标题为“打开文件”，过滤文件名*/
     fileName = QFileDialog::getOpenFileName(
                this,tr("打开文件"), "",
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
    graphicsScene->clear();
    /* 添加场景内容image */
    graphicsScene->addPixmap(image);

    tutitle->setText("文件名："+fileName);
}

void Tupian::startread()
{
    ocr->readyToDetection(fileName,true);
}


void Tupian::disPlaylprResult(QString result)
{
    if (result.isEmpty())
           tutitle->setText("    识别结果为：未识别！");
       else
           tutitle->setText("    识别结果为：" + result);

}

void Tupian::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void Tupian::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(release_x-press_x>50)
    {
         emit this->Tupianback();
        press_x=0;
        release_x=0;
    }
    if(press_x-release_x>50)
    {
         emit this->Tupianback();
        press_x=0;
        release_x=0;
    }
}
