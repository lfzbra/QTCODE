#ifndef LIFEWINDOW_H
#define LIFEWINDOW_H

#include <QMainWindow>

class LifeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LifeWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:
    void LifeWindowback();

};

#endif // LIFEWINDOW_H
