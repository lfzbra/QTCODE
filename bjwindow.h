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


class BJWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BJWindow(QWidget *parent = nullptr);



    QPushButton *Ledbtn;

    /* 设置lED的状态 */
    void setLedState(int set);

    /* 获取lED的状态 */
    bool getLedState();

    /* 文件 */
    QFile ledfile;
    QPushButton *Beepbtn;
    /* 文件 */
    QFile beepfile;
    /* 设置BEEP的状态 */
    void setBeepState(int set);

    /* 获取BEEP的状态 */
    bool getBeepState();

    QPushButton *Keybtn;
    /* 重写按键事件 */
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
       void BJWindowback();
private slots:
    void ledButtonClicked();
    void beepButtonClicked();

};

#endif // BJWINDOW_H
