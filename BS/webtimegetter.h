#ifndef WEBTIMEGETTER_H
#define WEBTIMEGETTER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QObject>
#include <QDateTime>
#include <QtNetwork/QUdpSocket>

class webTimeGetter : public QObject
{
    Q_OBJECT
public:
    explicit webTimeGetter(QObject *parent = nullptr);
public slots:
    void readingData(int endtime[]);
    void connectSucess();
    void tryGet();
private:
    QVector<QString> hostList;
    QUdpSocket*      udpsocket;
    QDateTime        time;
signals:
    void dateback();

};

#endif // WEBTIMEGETTER_H
