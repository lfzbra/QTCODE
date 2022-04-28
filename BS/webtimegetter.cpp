#include <iostream>
#include "webtimegetter.h"

webTimeGetter::webTimeGetter(QObject *parent) : QObject(parent)
{
    hostList.push_back("time.windows.com");
    hostList.push_back("time.nist.gov");
    udpsocket = new QUdpSocket(this);
    connect(udpsocket,SIGNAL(connected()),this,SLOT(connectSucess()));
    //connect(udpsocket,SIGNAL(readyRead()),this,SLOT(readingData()));
    connect(udpsocket,&QUdpSocket::readyRead,this,[=](){
        emit this->dateback();
    });
}
void webTimeGetter::readingData(int endtime[])
{
    QByteArray newTime;
    QDateTime epoch(QDate(1900, 1, 1));
    QDateTime unixStart(QDate(1970, 1, 1));
    do
    {
        newTime.resize(udpsocket->pendingDatagramSize());
        udpsocket->read(newTime.data(), newTime.size());
    }while(udpsocket->hasPendingDatagrams());
    QByteArray TransmitTimeStamp ;
    TransmitTimeStamp=newTime.right(8);
    quint32 seconds=TransmitTimeStamp[0];
    quint8 temp=0;
    for(int j=1;j<=3;j++)
    {
        seconds=seconds<<8;
        temp=TransmitTimeStamp[j];
        seconds=seconds+temp;
    }

    time.setTime_t(seconds-epoch.secsTo(unixStart));
//    qDebug()<<"年"<<time.date().year();
//    qDebug()<<"月"<<time.date().month();
//    qDebug()<<"日"<<time.date().day();
//    qDebug()<<"时"<<time.time().hour();
//    qDebug()<<"分"<<time.time().minute();
//    qDebug()<<"秒"<<time.time().second();
    int year = time.date().year();
    int month = time.date().month();
    int day = time.date().day();
    int hour = time.time().hour();
    int minute = time.time().minute();
    int second = time.time().second();
    //int endtime[6];
    endtime[0]=year;
    endtime[1]=month;
    endtime[2]=day;
    endtime[3]=hour;
    endtime[4]=minute;
    endtime[5]=second;




    udpsocket->disconnectFromHost();
    udpsocket->close();
}

void webTimeGetter::connectSucess()
{
    qint8 LI=0;
    qint8 VN=3;
    qint8 MODE=3;
    qint8 STRATUM=0;
    qint8 POLL=4;
    qint8 PREC=-6;
    QDateTime epoch(QDate(1900,1,1));
    qint32 second=quint32(epoch.secsTo(QDateTime::currentDateTime()));
    qint32 temp=0;
    QByteArray timeRequest(48, 0);
    timeRequest[0]=(LI <<6) | (VN <<3) | (MODE);
    timeRequest[1]=STRATUM;
    timeRequest[2]=POLL;
    timeRequest[3]=PREC & 0xff;
    timeRequest[5]=1;
    timeRequest[9]=1;
    timeRequest[40]=(temp=(second&0xff000000)>>24);
    temp=0;
    timeRequest[41]=(temp=(second&0x00ff0000)>>16);
    temp=0;
    timeRequest[42]=(temp=(second&0x0000ff00)>>8);
    temp=0;
    timeRequest[43]=((second&0x000000ff));
    udpsocket->flush();
    udpsocket->write(timeRequest);
    udpsocket->flush();
}

void webTimeGetter::tryGet()
{
    udpsocket->connectToHost(hostList.at(0),123);
}
