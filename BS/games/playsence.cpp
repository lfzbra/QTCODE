#include "playsence.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include "dataconfig.h"
#include<QMenuBar>
#include<QIcon>
#include<QTimer>
#include<QLabel>
#include<QPropertyAnimation>
#include<QSound>
#include "mycoin.h"
#include "mybutton.h"

PlaySence::PlaySence(int levelNum)
{
    QSound *mysound=new QSound(":/coin/ConFlipSound.wav",this);
     QSound *winsound=new QSound(":/coin/LevelWinSound.wav",this);

    qDebug()<<QString("进入了第 %1 关").arg(levelNum);
      this->levelIndex=levelNum;

    playsenceebtn = new MyButton(":/coin/BackButton");
    playsenceebtn->move(900,530);
    playsenceebtn->setParent(this);
    connect(playsenceebtn,&MyButton::clicked,this,[=](){
        emit this->PlaySenceback();
    });


    //显示当前关卡数
      QLabel *label=new QLabel;
      label->setParent(this);
      QFont font;
      font.setFamily("华为新魏");
      font.setPointSize(20);
      //将字体设置到标签控件中
      label->setFont(font);
      label->setText(QString("关卡:%1").arg(this->levelIndex));
   //   label->setStyleSheet("QLabel{border-radius: 4px;color:rgb(0,199,140);}");
   //   label->setStyleSheet("QLabel{color:rgb(0,199,140);}");
      label->setStyleSheet("QLabel{background:rgba(255,0,0,128);}");
      label->setGeometry(50,50,110,30);
      //label->move(100,500);


      dataConfig config;
     //初始化每个关卡的二维数组
      for(int i=0;i<4;i++)
      {
          for(int j=0;j<4;j++)
          {
              this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
          }
      }

      //胜利图片的显示
       QLabel *winLabel=new QLabel;
       QPixmap tmpPix;
       tmpPix.load(":/coin/LevelCompletedDialogBg.png");
       winLabel->setParent(this);
       winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
       winLabel->setPixmap(tmpPix);
       winLabel->move((this->width()-tmpPix.width())*1.9,-tmpPix.height());
       // winLabel->move(200,200);
       //显示金币的背景图
       for(int i=0;i<4;i++)
       {
           for(int j=0;j<4;j++)
           {
//               //绘制背景图片
//               QPixmap pix=QPixmap(":/coin/BoardNode(1).png");
//               QLabel *label=new QLabel;
//               label->setGeometry(0,0,100,100);
//               label->setPixmap(pix);
//               label->setParent(this);
//               label->move(300+i*120,100+j*100);

               //创建金币
               QString str;
               if(this->gameArray[i][j]==1)
               {
                   //显示金币
                   str=":/coin/Coin0001.png";

               }
               else{
                   str=":/coin/Coin0008.png";
               }

               MyCoin *coin=new MyCoin(str);
               coin->setParent(this);
               coin->move(300+i*120,100+j*100);

               //给金币的属性赋值
               coin->posX=i;
               coin->posY=j;
               coin->flag=this->gameArray[i][j]; //  1正面 0反面

               //将金币放入到金币的二维数组里面 以便于后期的维护
               coinBtn[i][j]=coin;


               //点击金币进行翻转
               connect(coin,&MyCoin::clicked,[=](){
                   coin->changeFlag();
                   mysound->play();
                   this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

                   QTimer::singleShot(300,this,[=](){
                       // 翻转周围硬币的操作，延时翻转
                       if(coin->posX+1<=3){// 周围的右侧硬币翻转的条件
                           coinBtn[coin->posX+1][coin->posY]->changeFlag();
                           this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;

                       }
                       if(coin->posX-1>=0) // 周围左侧硬币的翻转条件
                       {
                           coinBtn[coin->posX-1][coin->posY]->changeFlag();
                           this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                       }
                       if(coin->posY+1<=3) // 周围下侧硬币的翻转条件
                       {
                           coinBtn[coin->posX][coin->posY+1]->changeFlag();
                           this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                       }
                       if(coin->posY-1>=0) // 周围上侧硬币的翻转条件
                       {
                           coinBtn[coin->posX][coin->posY-1]->changeFlag();
                           this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                       }

                       //判断是否胜利
                       this->isWin=true;
                       for(int i=0;i<4;i++)
                       {
                           for(int j=0;j<4;j++){
                               if(coinBtn[i][j]->flag==false){
                                   this->isWin=false;
                                   break;
                               }
                           }
                       }

                       if(this->isWin==true){
                           //胜利了
                           qDebug()<<"游戏胜利";
                           //winsound->play();
                         //  endPlayer->setMedia(QUrl::fromLocalFile("F:/QTproj/data820/learn/Config/coin/bkmusic.mp3"));
                           //endPlayer->setMedia(QUrl("/coin/bkmusic.mp3"));
//                           endPlayer->setMedia(QUrl::fromLocalFile(QStringLiteral("coin/bkmusic.mp3")));
//                           endPlayer->setVolume(100);
//                           endPlayer->play();






                           //将所有按钮胜利的标志改为 true,如果再次点击按钮直接return
                           for(int i=0;i<4;i++)
                           {
                               for(int j=0;j<4;j++){
                                   coinBtn[i][j]->isWin=true;
                               }
                           }

                           //将胜利的图片移动下来
                           QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                           //设置时间间隔
                           animation->setDuration(1000);

                           //设置开始位置
                           animation->setStartValue(QRect(QPoint(winLabel->x(),winLabel->y()),QPoint(winLabel->x()+winLabel->width(),winLabel->height())));
                           //设置结束位置
                           animation->setEndValue(QRect(QPoint(winLabel->x(),winLabel->y()+200),QPoint(winLabel->x()+winLabel->width(),winLabel->height()+120)));

                           //设置缓和曲线
                           animation->setEasingCurve(QEasingCurve::OutBounce);
                           //执行动画
                           animation->start();
                           //


                       }

                   });

               });

           }
       }




}


void PlaySence::paintEvent(QPaintEvent *)
{
    QPainter paintercoin(this);
    QPixmap pixcoin;
    pixcoin.load(":/coin/OtherSceneBg.png");
    paintercoin.drawPixmap(0,0,this->width(),this->height(),pixcoin);
}

void PlaySence::icomShow(QString path1,QString path2,QPainter* painter)
{
//    QPixmap pix;
//    bool ret=pix.load(path1);
//    if(!ret){
//        qDebug()<<"图片加载失败";
//        return;
//    }

//    painter->drawPixmap(0,0,this->width(),this->height(),pix);

//    //加载标题
//    pix.load(path2);
//    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
//    painter->drawPixmap(10,30,pix.width(),pix.height(),pix);
}

