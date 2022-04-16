#include "cwwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include<QtSerialPort>
#include<QSerialPortInfo>
#include<QString>
#include <QFile>
#include <QPixmap>
#include <QBuffer>
#include "camera.h"
#include <QMouseEvent>
#include <QDateTime>
#include <QTime>
#include <QMediaPlayer>
#include <QSound>

CWWindow::CWWindow(QWidget *parent) : QMainWindow(parent)
{
   startSound1=new QSound(":/cwMusic/wenduyichang_1.wav",this);
   startSound=new QSound(":/cwMusic/wenduzhengchang_1.wav",this);
     serialPort = new QSerialPort(this);
    cwbtn = new QPushButton("测温",this);
    cwbtn->setGeometry(700,500,100,70);
    connect(cwbtn,&QPushButton::clicked,this,[=](){
                /*串口初始化*/
               SerialInit();
             if (!serialPort->open(QIODevice::ReadWrite))
                {
                 qDebug()<<"打开串口失败";
                 }
               else serialSend();
    });
    /*串口触发*/
    connect(serialPort, SIGNAL(readyRead()),
            this, SLOT(serialPortReadyRead()));

    CLbtn =new QPushButton("返回",this);
    CLbtn->setGeometry(900, 500, 100, 70);
    connect(CLbtn,&QPushButton::clicked,this,[=](){
        serialPort->close();
        emit this->CWWindowback();
    });
    /* 布局初始化 */
    layoutInit();

    /* 扫描摄像头 */
    scanCameraDevice();


}

void CWWindow::SerialInit()
{
    /* 设置串口名 */
    serialPort->setPortName("ttymxc2");
    /* 设置波特率 */
    serialPort->setBaudRate(9600);
    /* 设置数据位数 */
     serialPort->setDataBits(QSerialPort::Data8);
     /* 设置停止位 */
     serialPort->setStopBits(QSerialPort::OneStop);
     /* 设置流控制 */
     serialPort->setFlowControl(QSerialPort::NoFlowControl);

}

void CWWindow::serialPortReadyRead()
{
    /*温度数据*/
    int num[10];
    int flag=0;

    /* 接收缓冲区中读取数据 */
   QByteArray buf = serialPort->readAll();
    qDebug()<<buf.toHex();
    QDataStream out(&buf,QIODevice::ReadWrite);
    QString buf1;
    while(!out.atEnd())
       {
             qint8 outChar = 0;
             out >> outChar;
             QString str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");
             buf1 += str;
             bool ok = false;
            num[flag]=str.toInt(&ok, 16);
             qDebug()<<"num="<<num[flag];
             flag++;
             if(flag>=10)
                 flag=0;
       }
    wtnum=(double)(num[4]*256+num[5])/100;
    hjnum=(double)(num[6]*256+num[7])/100;
    qDebug()<<"wtnum="<<wtnum;
    qDebug()<<"hjnum="<<hjnum;
    QString s = QString("目标温度：%1").arg(wtnum);
    wtnumbtn->setText(s);
    QString s1 =QString("环境温度：%1").arg(hjnum);
    hjnumbtn->setText(s1);

    if(wtnum>37.5)
    {
        startSound1->play();
        qDebug()<<"异常";
    }
    else
    {
        qDebug()<<"正常";
        startSound->play();
    }
    serialPort->close();
    saveImageToLocal();
}

void CWWindow::serialSend()
{
    QByteArray num;
    num[0]=0xa5;
    num[1]=0x15;
    num[2]=0xba;
    serialPort->write(num);
}

void CWWindow::layoutInit()
{
    /* 获取屏幕的分辨率，Qt官方建议使用这
     * 种方法获取屏幕分辨率，防上多屏设备导致对应不上
     * 注意，这是获取整个桌面系统的分辨率
     */
    QList <QScreen *> list_screen =  QGuiApplication::screens();

    /* 如果是ARM平台，直接设置大小为屏幕的大小 */
#if __arm__
    /* 重设大小 */
    this->resize(list_screen.at(0)->geometry().width(),
                 list_screen.at(0)->geometry().height());
#else
    /* 否则则设置主窗体大小为800x480 */
    this->resize(800, 480);
#endif

    /* 实例化与布局，常规操作 */
    mainWidget = new QWidget();
    photoLabel = new QLabel();
    rightWidget = new QWidget();
    comboBox = new QComboBox();
    pushButton[0] = new QPushButton();
    pushButton[1] = new QPushButton();
    scrollArea = new QScrollArea();
    displayLabel = new QLabel(scrollArea);
    vboxLayout = new QVBoxLayout();
    hboxLayout = new QHBoxLayout();
    upvboxLayout= new QVBoxLayout();
    upWidget = new QWidget();
    wtnumbtn = new QPushButton("目标温度：00.00",this);
    hjnumbtn = new QPushButton("环境温度：00.00",this);
    liftWidget = new QWidget;
    uphboxLayout = new QHBoxLayout;

    vboxLayout->addWidget(photoLabel);
    vboxLayout->addWidget(comboBox);
    //vboxLayout->addWidget(pushButton[0]);
    vboxLayout->addWidget(pushButton[1]);
    vboxLayout->addWidget(cwbtn);
    vboxLayout->addWidget(CLbtn);


    uphboxLayout->addWidget(wtnumbtn);
    uphboxLayout->addWidget(hjnumbtn);
    upWidget->setLayout(uphboxLayout);
    upvboxLayout->addWidget(upWidget);
    upvboxLayout->addWidget(scrollArea);
    liftWidget->setLayout(upvboxLayout);

    rightWidget->setLayout(vboxLayout);


    hboxLayout->addWidget(liftWidget);
    hboxLayout->addWidget(rightWidget);
    mainWidget->setLayout(hboxLayout);



    this->setCentralWidget(mainWidget);

    wtnumbtn->setMaximumHeight(50);
    wtnumbtn->setMaximumWidth(300);
    hjnumbtn->setMaximumHeight(50);
    hjnumbtn->setMaximumWidth(300);

    pushButton[1]->setMaximumHeight(40);
    pushButton[1]->setMaximumWidth(200);

    pushButton[1]->setMaximumHeight(40);
    pushButton[1]->setMaximumWidth(200);

    CLbtn->setMaximumHeight(40);
    CLbtn->setMaximumWidth(200);
    cwbtn->setMaximumHeight(40);
    cwbtn->setMaximumWidth(200);

    comboBox->setMaximumHeight(40);
    comboBox->setMaximumWidth(200);
    photoLabel->setMaximumSize(100, 75);
    scrollArea->setMinimumWidth(this->width()
                                - comboBox->width());

    /* 显示图像最大画面为xx */
    displayLabel->setMinimumWidth(scrollArea->width() * 0.75);
    displayLabel->setMinimumHeight(scrollArea->height() *0.75);
    scrollArea->setWidget(displayLabel);

    /* 居中显示 */
    scrollArea->setAlignment(Qt::AlignCenter);

    /* 自动拉伸 */
    photoLabel->setScaledContents(true);
    displayLabel->setScaledContents(true);

    /* 设置一些属性 */
    pushButton[0]->setText("拍照");
    pushButton[0]->setEnabled(false);
    pushButton[1]->setText("开始");
    pushButton[1]->setCheckable(true);
     cwbtn->setEnabled(false);

    /* 摄像头 */
    camera = new Camera(this);

    /* 信号连接槽 */
    connect(camera, SIGNAL(readyImage(QImage)),
            this, SLOT(showImage(QImage)));
    connect(pushButton[1], SIGNAL(clicked(bool)),
            camera, SLOT(cameraProcess(bool)));
    connect(pushButton[1], SIGNAL(clicked(bool)),
            this, SLOT(setButtonText(bool)));
//    connect(cwbtn, SIGNAL(clicked()),
//            this, SLOT(saveImageToLocal()));

}

void CWWindow::scanCameraDevice()
{
    /* 如果是Windows系统，一般是摄像头0 */
#if win32
    comboBox->addItem("windows摄像头0");
    connect(comboBox,
            SIGNAL(currentIndexChanged(int)),
            camera, SLOT(selectCameraDevice(int)));
#else
    /* QFile文件指向/dev/video0 */
    QFile file("/dev/video0");

    /* 如果文件存在 */
    if (file.exists())
        comboBox->addItem("video0");
    else {
        displayLabel->setText("无摄像头设备");
        return;
    }

    file.setFileName("/dev/video1");

    if (file.exists()) {
        comboBox->addItem("video1");
        /* 开发板ov5640等设备是1 */
        comboBox->setCurrentIndex(1);
    }

    file.setFileName("/dev/video2");

    if (file.exists())
        /* 开发板USB摄像头设备是2 */
        comboBox->addItem("video2");

#if !__arm__
    /* ubuntu的USB摄像头一般是0 */
    comboBox->setCurrentIndex(0);
#endif

    connect(comboBox,
            SIGNAL(currentIndexChanged(int)),
            camera, SLOT(selectCameraDevice(int)));
#endif
}

void CWWindow::showImage(const QImage &image)
{
    /* 显示图像 */
    displayLabel->setPixmap(QPixmap::fromImage(image));
    saveImage = image;

    /* 判断图像是否为空，空则设置拍照按钮不可用 */
    if (!saveImage.isNull())
        cwbtn->setEnabled(true);
    else
        cwbtn->setEnabled(false);
}

void CWWindow::setButtonText(bool bl)
{
    if (bl) {
        /* 设置摄像头设备 */
        camera->selectCameraDevice(comboBox->currentIndex());
        pushButton[1]->setText("关闭");
    } else {
        /* 若关闭了摄像头则禁用拍照按钮 */
        pushButton[0]->setEnabled(false);
        pushButton[1]->setText("开始");
    }
}

void CWWindow::saveImageToLocal()
{
    /* 判断图像是否为空 */
    if (!saveImage.isNull()) {
        //时间获取和设置
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy.MM.dd-hh:mm:ss.zzz-ddd");
//        QTime current_time =QTime::currentTime();
//        int a = current_time.hour();
//        int b = current_time.minute();
//        int c = current_time.second();
//        QString hour = QString::number(a);
//        QString minute = QString::number(b);
//        QString second = QString::number(c);
//        qDebug()<<"a="<<a<<"b="<<b<<"c="<<c<<"hour="<<hour<<"minute="<<minute<<"second="<<second<<"current_time"<<current_time;
        QString fileName =
                QString("/home/root/photo/"+current_date+"test-%1.png").arg(wtnum);
        qDebug()<<"正在保存"<<fileName<<"图片,请稍候..."<<endl;

        /* save(arg1，arg2，arg3)重载函数，arg1代表路径文件名，
         * arg2保存的类型，arg3代表保存的质量等级 */
        saveImage.save(fileName, "PNG", -1);

        /* 设置拍照的图像为显示在photoLabel上 */
        photoLabel->setPixmap(QPixmap::fromImage(QImage(fileName)));

        qDebug()<<"保存完成！"<<endl;

    }
}

void CWWindow::mousePressEvent(QMouseEvent *event)
{
    press_x=event->x();
    press_y=event->y();
    qDebug()<<"按下x: %1,y: %1"<<press_x<<press_y;
}

void CWWindow::mouseReleaseEvent(QMouseEvent *event)
{
    release_x=event->x();
    release_y=event->y();
    qDebug()<<"松开x: %1,y: %1"<<press_x<<press_y;

    if(press_x-release_x>50)
    {
        emit this->CWWindowback();
        press_x=0;
        release_x=0;
   }

}
