#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "mybutton.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

    //重写paintEvent事件  画背景图
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;

    MyButton *coinbtn;
    MyButton *backlifebtn;

signals:
    void GameWindowback();
};

#endif // GAMEWINDOW_H
