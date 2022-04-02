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

};
#endif // MAINWINDOW_H
