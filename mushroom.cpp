#include "mushroom.h"
#include<QDebug>
#include<QRandomGenerator>
#include"platform.h"
Mushroom::Mushroom()
{
    int x = (QRandomGenerator::global()->generate()) %4;

    switch (x) {
    case 0:{
        setPixmap(QPixmap(":/images/mushroom1.png"));
        break;}
    case 1:{
        setPixmap(QPixmap(":/images/mushroom2.png"));
        break;}
    case 2:{
        setPixmap(QPixmap(":/images/mushroom3.png"));
        break;}
    case 3: {
        setPixmap(QPixmap(":/images/mushroom4.png"));
        break;}
    case 4: {
        setPixmap(QPixmap(":/images/mushroom5.png"));
        break;}


    }

    setZValue(-1);

    timer= new QTimer;
}


void Mushroom::start()
{



    qDebug()<<"mushroom start";
    AirState=-1;
    yAnimationUp->stop();
    yAnimationUp->setStartValue(y());
    yAnimationUp->setEndValue(y()-55);
    yAnimationUp->setDuration(1000);
    yAnimationUp->setEasingCurve(QEasingCurve::Linear);
    yAnimationUp->start();
    connect(yAnimationUp,&QPropertyAnimation::finished,[=](){
        xAnimation->setStartValue(x());
        xAnimation->setEndValue(x()+3000);
        xAnimation->setDuration(10000);
        xAnimation->setEasingCurve(QEasingCurve::Linear);
        direction=0;
        groundState=1;
        AirState=0;
        xAnimation->start();
        connect(xAnimation,&QPropertyAnimation::finished,[=](){
            delete this;
        });
    });

}

//******************************   --Collision Detection --  ******************************************

bool Mushroom::collideX()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        if ((platform))
        {
            qreal t;
            t=this->y();
            if ((item->y()>t) && (item->y()<t+pixmap().width()))
                if (((direction==0) && (item->x()>=this->x())) || ((direction==1) && (item->x()<=this->x())) )
                    return true;
        }
    }
    return false;
}
//-------------------------------------------------------------------------------------
QString Mushroom::collideY()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        if (platform)
        {
                  if ((platform->getPlatformType()!=-1) || (platform->getPlatformType()!=4))
                    return "foots";


        }
    }
    return "notcolliding";
}

//******************************    --Positioning--      *********************************

qreal Mushroom::y() const
{
    return m_y;
}
//-------------------------------------------------------------------------------------
qreal Mushroom::x() const
{
    return m_x;
}
//-------------------------------------------------------------------------------------
void Mushroom::setY(qreal y)
{
    m_y = y;
    if (collideY()!="notcolliding") // colliding
    {
        if ((collideY()=="foots") && (AirState==2))
        {
            stopFalling();
            m_y=y-27;
            if (AirState!=0)
                AirState=0;

        }

    }
    setPos(QPoint(0,0)+QPoint(x(),m_y));
}
//-------------------------------------------------------------------------------------
void Mushroom::setX(qreal x)
{
    m_x = x;
    if (collideX())
    {
        if (direction==0)
            m_x = x-10;
        else
            m_x = x+10;
        xAnimation->stop();
    }
    else
        if (collideY()=="notcolliding")
        {
            if (AirState==0)
                fall(500-y(),y(),500);
        }
    setPos(QPoint(0,0)+QPoint(m_x,y()));
}
