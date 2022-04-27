#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cwwindow.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QDebug>
#include "bjwindow.h"
#include "cwwindow.h"
#include "lifewindow.h"
#include <QTimer>
#include <QString>
#include <QTime>
#include <QLCDNumber>
#include <webtimegetter.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //報警界面按鍵
    QPushButton *BJbtn;

    //重写paintEvent事件  画背景图
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    QTimer *timer;
    QLCDNumber *lcdnumber;
private:
    webTimeGetter *webtime;
    int endtime[6];
    int press_x;
    int press_y;
    int release_x;
    int release_y;
    QLabel *label;

    CWWindow *CwWin;
    LifeWindow *next;
private slots:
 /* 槽函数 */
 void timerTimeOut();

};
#endif // MAINWINDOW_H
