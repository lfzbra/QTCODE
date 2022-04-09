#ifndef COINCHOICE_H
#define COINCHOICE_H

#include <QMainWindow>
#include<QPushButton>
#include "playsence.h"
#include "mybutton.h"

class CoinChoice : public QMainWindow
{
    Q_OBJECT
public:
    explicit CoinChoice(QWidget *parent = nullptr);
    //重写paintEvent事件  画背景图
    void paintEvent(QPaintEvent *);

    //游戏场景的绘图指针
     PlaySence *play = NULL;

     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);

private:
    MyButton *coinchoicebtn;
    int press_x;
    int press_y;
    int release_x;
    int release_y;

signals:
    void CoinChoiceback();
};

#endif // COINCHOICE_H
