#ifndef COINGAME_H
#define COINGAME_H

#include <QMainWindow>
#include"QPushButton"
#include "mybutton.h"

class CoinGame : public QMainWindow
{
    Q_OBJECT
public:
    explicit CoinGame(QWidget *parent = nullptr);
    //重写paintEvent事件  画背景图
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);



private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;
   MyButton *back;

   MyButton *startbtn;

   MyButton *titlebtn;

signals:
    void CoinGameback();
};

#endif // COINGAME_H
