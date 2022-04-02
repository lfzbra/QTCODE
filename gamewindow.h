#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

signals:
    void GameWindowback();
};

#endif // GAMEWINDOW_H
