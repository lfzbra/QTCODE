#ifndef PICTUREWINDOW_H
#define PICTUREWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class PictureWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PictureWindow(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void Picturedelete();

private:
    int press_x;
    int press_y;
    int release_x;
    int release_y;

    QVBoxLayout *rvboxlayout;
    QVBoxLayout *lvboxlayout;
    QHBoxLayout *hboxlayout;
    QWidget *rightwidget;
    QWidget *liftwidget;
    QPushButton *openbtn;
    QPushButton *back;
    QPushButton *deletebtn;
    QPushButton *deleteallbtn;
    QLabel *namelabel;
    QWidget *mainwidget;
    /* 声明对象 */
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;

signals:

    void PictureWindowback();


private slots:
    /* 槽函数 */
    void openActionTriggered();

};

#endif // PICTUREWINDOW_H
