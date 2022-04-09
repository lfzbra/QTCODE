#ifndef CWWINDOW_H
#define CWWINDOW_H
#include <QMainWindow>
#include <QObject>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include<QtSerialPort>
#include<QSerialPortInfo>
#include<QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QMediaPlayer>
#include <QSound>
class Camera;

class CWWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CWWindow(QWidget *parent = nullptr);
     QSerialPort *serialPort;
     /*串口初始化*/
    void SerialInit();
    /*串口发送函数*/
    void serialSend();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QSound* startSound;
    QSound* startSound1;
    QMediaPlayer *endPlayer;
    QMediaPlayer *endPlayer1;
    double wtnum=0;
    double hjnum=0;

    int press_x;
    int press_y;
    int release_x;
    int release_y;
    int num=0;
    QPushButton *CLbtn;

    QPushButton *cwbtn;

    /* 主容器，Widget也可以当作一种容器 */
    QWidget *mainWidget;

    /* 滚动区域，方便开发高分辨率 */
    QScrollArea *scrollArea;

    /* 将采集到的图像使用Widget显示 */
    QLabel *displayLabel;

    /* 界面右侧区域布局 */
    QHBoxLayout *hboxLayout;

    /* 界面右侧区域布局 */
    QVBoxLayout *vboxLayout;

    /* 界面右侧区域容器 */
    QWidget *rightWidget;

    /* 界面右侧区域显示拍照的图片 */
    QLabel *photoLabel;

    /* 界面右侧区域摄像头设备下拉选择框 */
    QComboBox *comboBox;

    /* 两个按钮，一个为拍照按钮，另一个是开启摄像头按钮 */
    QPushButton *pushButton[2];

    /* 拍照保存的照片 */
    QImage saveImage;

    /* 摄像头设备 */
    Camera *camera;

    /* 布局初始化 */
    void layoutInit();

    /* 扫描是否存在摄像头 */
    void scanCameraDevice();

    /* 界面右侧区域容器 */
    QWidget *upWidget;
    QWidget *liftWidget;

    /* 界面右侧区域布局 */
    QVBoxLayout *upvboxLayout;
    QHBoxLayout *uphboxLayout;
    QPushButton *wtnumbtn;
    QPushButton *hjnumbtn;

signals:
    void CWWindowback();
private slots:
    void serialPortReadyRead();
    /* 显示图像 */
    void showImage(const QImage&);

    /* 设置按钮文本 */
    void setButtonText(bool);

    /* 保存照片到本地 */
    void saveImageToLocal();


};

#endif // CWWINDOW_H
