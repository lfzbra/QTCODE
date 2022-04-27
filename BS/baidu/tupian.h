#ifndef TUPIAN_H
#define TUPIAN_H

#include <QMainWindow>
#include<QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include "ocr.h"
#include <QGraphicsView>
#include <QMouseEvent>

class Tupian : public QMainWindow
{
    Q_OBJECT
public:
    explicit Tupian(QWidget *parent = nullptr);
    void layoutInit();
    void openfile();
    void startread();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void disPlaylprResult(QString);
private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;
    /* 声明对象 */
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    //Ocr *ocr;
    Ocr *ocr;
    QString fileName;
    QPushButton *tupianbackbtn;

    QLabel *tulabel;
    QLabel *tutitle;
    QPushButton *openbtn;
    QPushButton *startbtn;
    QPushButton *plantbtn;
    QVBoxLayout *rvboxlayout;
    QHBoxLayout *hboxlayout;
    QVBoxLayout *lvboxlayout;

    QWidget *rwidget;
    QWidget *lwidget;
    QWidget *mainwidget;


signals:
    void Tupianback();
};

#endif // TUPIAN_H
