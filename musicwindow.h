#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QMainWindow>

class MusicWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MusicWindow(QWidget *parent = nullptr);

signals:
    void MCWindowback();
};

#endif // MUSICWINDOW_H
