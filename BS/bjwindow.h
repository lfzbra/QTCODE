#ifndef BJWINDOW_H
#define BJWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QFile>
#include <QString>
#include <QEvent>
#include "mybutton.h"

class BJWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BJWindow(QWidget *parent = nullptr);
    /* 设置lED的状态 */
    void setLedState(int set);

    /* 文件 */
    QFile ledfile;
    /* 文件 */
    QFile beepfile;
    /* 设置BEEP的状态 */
    void setBeepState(int set);

    QPushButton *Keybtn;
    /* 重写按键事件 */
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    MyButton *ledbnl;
    MyButton *beepbnl;
    MyButton *ledbnm;
    MyButton *beepbnm;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;
signals:
       void BJWindowback();
private slots:
    void ledButtonClicked();
    void beepButtonClicked();

};

#endif // BJWINDOW_H
