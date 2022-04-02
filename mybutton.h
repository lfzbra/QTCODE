#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyButton(QWidget *parent = nullptr);
    MyButton(QString nom);

    void zoom1(void);
    void zoom2(void);

    QString nompath;
    QString presspath;
signals:

};

#endif // MYBUTTON_H
