#include "mushroom.h"
#include<QDebug>
#include<QRandomGenerator>
#include"platform.h"
#include"player.h"
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
    yAnimationUp->setEndValue(y()-65);
    yAnimationUp->setDuration(1000);
    yAnimationUp->setEasingCurve(QEasingCurve::Linear);
    yAnimationUp->start();
    connect(yAnimationUp,&QPropertyAnimation::finished,[=](){
    walk(1);
        });

}

void Mushroom::walk(int direc)
{
    xAnimation->stop();
    xAnimation->setStartValue(x());
    if (direc==1)
        xAnimation->setEndValue(x()+3000);
    else xAnimation->setEndValue(x()-3000);
    xAnimation->setDuration(10000);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    groundState=direc;
    AirState=0;
    xAnimation->start();
}

//******************************   --Collision Detection --  ******************************************

QString Mushroom::collideX()
{
    qreal t;
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        InanimateObject * inanimateObject =dynamic_cast<InanimateObject*>(item);
        Player * player =dynamic_cast<Player*>(item);
        if ((platform))
        {

            t=this->y();
            if ((item->y()<t) )
                if (((direction==0) && (item->x()>=this->x())) || ((direction==1) && (item->x()<=this->x())) )
                    return "collide";
        }
        else
            if (inanimateObject)
            {
                t=this->y();
                if ((inanimateObject->y()<t) )
                    if (((direction==0) && (inanimateObject->x()>=this->x())) || ((direction==1) && (inanimateObject->x()<=this->x())) )
                        return "collide";

            }
        else
        if (player)
        {
            player->powerup();
            return "player";

        }
    }
    return "notcolliding";
}
//-------------------------------------------------------------------------------------
QString Mushroom::collideY()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        if ((platform) && (AirState!=-1))
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
            m_y=y-10;
            if (AirState!=0)
                AirState=0;
        }
    }
    setPos(x(),m_y);
}
//-------------------------------------------------------------------------------------
void Mushroom::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
    if (collideX()=="collide")
    {
        if (groundState==1)
        {
            m_x = x-20;
            xAnimation->stop();
            walk(2);
        }
        else
        {
          //  m_x = x+20;
            walk(1);
        }
    }
    else
        if (collideX()=="player")
        {

            delete this;
        }
    else
        if (collideY()=="notcolliding")
        {
            if (AirState==0)
                fall(1000-y(),y(),500);

        }

}
