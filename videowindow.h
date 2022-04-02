#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QMainWindow>

class VideoWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit VideoWindow(QWidget *parent = nullptr);

signals:
    void VideoWindowback();
};

#endif // VIDEOWINDOW_H
