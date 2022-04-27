#ifndef PHOTOGRAPHY_H
#define PHOTOGRAPHY_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include "ocr.h"
#include <QMouseEvent>

class Camera;

class Photography : public QMainWindow
{
    Q_OBJECT
public:
    explicit Photography(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;
    Ocr *ocr;
    QPushButton *photographyback;
    QPushButton *startbtn;
    QPushButton *plantbtn;
    QLabel *namelabel;
    QWidget *lwidget;
    QVBoxLayout *lvboxlayout;
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

private slots:
    /* 显示图像 */
    void showImage(const QImage&);

    /* 设置按钮文本 */
    void setButtonText(bool);

    /* 保存照片到本地 */
    void saveImageToLocal();

    void disPlaylprResult(QString);
signals:
    void Photographyback();

};

#endif // PHOTOGRAPHY_H
