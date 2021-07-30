#include "platform.h"
#include<QDebug>
#include<QParallelAnimationGroup>
#include<QRandomGenerator>


Platform::Platform(int platformType,int x,int y)
{
    switch (platformType) {
    case 1:{
        Graphicsplateform = new QGraphicsPixmapItem(QPixmap(":/images/groundPlateform.png"));
        addToGroup(Graphicsplateform);
        typePlatform=1;
        break;}
    case 2:{
        Graphicsplateform = new QGraphicsPixmapItem(QPixmap(":/images/AirPlateform.png"));
        addToGroup(Graphicsplateform);
        typePlatform=2;
        break;}
    case 3: {
        Graphicsplateform = new QGraphicsPixmapItem(QPixmap(":/images/Bricks.png"));
        addToGroup(Graphicsplateform);
        typePlatform=3;
        //******************* destroyed animation
        collapseSound=new QMediaPlayer();
        collapseSound->setMedia(QUrl("qrc:/sound/sound/break.mp3"));
        BrikAnimation = new QParallelAnimationGroup;
        for(int i=0;i<15;i++)
        {
         briksArray[i] = new Briks(i%2);

         yAnimationArrayUp[i]=new QPropertyAnimation(briksArray[i],"y");
         yAnimationArrayDown[i]=new QPropertyAnimation(briksArray[i],"y");
         yAnimationArrayUp[i]=new QPropertyAnimation(briksArray[i],"y");
         xAnimationArray[i]=new QPropertyAnimation(briksArray[i],"x");

         yAnimation[i]= new QSequentialAnimationGroup;
        int x = (QRandomGenerator::global()->generate()) %200;
         yAnimationArrayUp[i]->setStartValue(briksArray[i]->y());
         yAnimationArrayUp[i]->setEndValue(briksArray[i]->y()-x);
         yAnimationArrayUp[i]->setDuration(100+x);
         yAnimationArrayUp[i]->setEasingCurve(QEasingCurve::OutQuint);
         yAnimation[i]->addAnimation(yAnimationArrayUp[i]);


        yAnimationArrayDown[i]->setStartValue(briksArray[i]->y()-x);
        yAnimationArrayDown[i]->setEndValue(briksArray[i]->y()+1000);
        yAnimationArrayDown[i]->setDuration(1000);
        yAnimationArrayDown[i]->setEasingCurve(QEasingCurve::Linear);
         yAnimation[i]->addAnimation(yAnimationArrayDown[i]);

        //*****************************************************
        x = (QRandomGenerator::global()->generate()) %300;
         xAnimationArray[i]->setStartValue(briksArray[i]->x());
         if (i%2==0)
         xAnimationArray[i]->setEndValue(briksArray[i]->x()+x+100);
         else xAnimationArray[i]->setEndValue(briksArray[i]->x()-x-100);

         xAnimationArray[i]->setDuration(1700);
         xAnimationArray[i]->setEasingCurve(QEasingCurve::OutQuint);

         //******************************************************************


         BrikAnimation->addAnimation(yAnimation[i]);

         //*****************************************
          BrikAnimation->addAnimation(xAnimationArray[i]);

        }

        break;}
    case 4: {
        questbox= new Questbox();
        addToGroup(questbox);
        typePlatform=4;
        SeqtouchedAnimation=new QSequentialAnimationGroup;
        touchedAnimationUp=new QPropertyAnimation(this,"y");
        touchedAnimationDown=new QPropertyAnimation(this,"y");
        break;}
    case 5:{
        Graphicsplateform = new QGraphicsPixmapItem(QPixmap(":/images/metalBlok.png"));
        addToGroup(Graphicsplateform);
        typePlatform=6;
        break;}

    }

xPos=x;
yPos=y;
firstToutchtimer= new QTimer();
setY(y);
setX(x);




}

int Platform::getPlatformType()
{
    return typePlatform;
}

void Platform::destroyPlatform()
{
    if (typePlatform==3)
    {
    collapseSound->play();
    connect(firstToutchtimer, &QTimer::timeout, this,[=](){
      Graphicsplateform->setVisible(false);
      typePlatform=-1;
      removeFromGroup(Graphicsplateform);
     for(int i=0;i<15;i++)
       addToGroup(briksArray[i]);
     BrikAnimation->start();
     firstToutchtimer->stop();
      // addToGroup(Graphicsplateform);
      connect(BrikAnimation, &QParallelAnimationGroup::finished, this,[=](){
          delete this;
      });

      });
        firstToutchtimer->start(20);
     }
}

void Platform::Touched()
{

    touchedAnimationUp->stop();
    touchedAnimationUp->setStartValue(yPos);
    touchedAnimationUp->setEndValue(yPos-20);
    touchedAnimationUp->setDuration(150);
    touchedAnimationUp->setEasingCurve(QEasingCurve::Linear);
    touchedAnimationUp->start();
    connect(touchedAnimationUp,&QPropertyAnimation::finished,[=](){

        touchedAnimationDown->setStartValue(yPos-20);
        touchedAnimationDown->setEndValue(yPos);
        touchedAnimationDown->setDuration(300);
        touchedAnimationDown->setEasingCurve(QEasingCurve::Linear);
        touchedAnimationDown->start();
        connect(touchedAnimationDown,&QPropertyAnimation::finished,[=](){

           if (numberItem>0)
           {
           mushroom= new Mushroom();
           mushroom->setX(x());
           mushroom->setY(y());
           scene()->addItem(mushroom);
          // addToGroup(mushroom);
           mushroom->start();
           numberItem=-numberItem;
           }
        });

    });
//*********************************************************
}

qreal Platform::y() const
{
    return m_y;
}

qreal Platform::x() const
{
    return m_x;
}

void Platform::setY(qreal y)
{
    m_y = y;
    setPos(x(),y);
}

void Platform::setX(qreal x)
{
    m_x = x;
    setPos(x,y());
}
