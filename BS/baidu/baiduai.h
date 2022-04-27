#ifndef BAIDUAI_H
#define BAIDUAI_H

#include <QMainWindow>
#include <QPushButton>
#include "photography.h"
#include <QMouseEvent>

class BaiduAI : public QMainWindow
{
    Q_OBJECT
public:
    explicit BaiduAI(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;
    QPushButton *baidubackbtn;
    QPushButton *tupianbtn;
    QPushButton *photographybtn;

signals:
    void BaiduAIback();
};

#endif // BAIDUAI_H
