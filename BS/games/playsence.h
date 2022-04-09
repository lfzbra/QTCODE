#ifndef PLAYSENCE_H
#define PLAYSENCE_H

#include <QMainWindow>
#include <QPushButton>
#include "dataconfig.h"
#include <QMediaPlayer>
#include<QDebug>
#include "mycoin.h"
#include "mybutton.h"

class PlaySence : public QMainWindow
{
    Q_OBJECT
public:
   // explicit PlaySence(QWidget *parent = nullptr);
    PlaySence(int levelNum);
    int levelIndex;//内部成员属性 记录所选的关卡

    //重写paintEvent 事件
    void paintEvent(QPaintEvent *);
    void icomShow(QString path1,QString path2,QPainter* painter);

    //二维数组维护每关关卡的具体数据
    int gameArray[4][4];
    MyCoin * coinBtn[4][4];

    //是否胜利的标志
    bool isWin=false;
    QMediaPlayer *endPlayer;

private:
   MyButton *playsenceebtn;

signals:
    void PlaySenceback();
};

#endif // PLAYSENCE_H
