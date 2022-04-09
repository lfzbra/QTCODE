#ifndef LIFEWINDOW_H
#define LIFEWINDOW_H

#include <QMainWindow>
#include "mybutton.h"
#include <QMouseEvent>

class LifeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LifeWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    MyButton *Backbtn;
private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;

signals:
    void LifeWindowback();

};

#endif // LIFEWINDOW_H
