#include "star.h"
#include"platform.h"
#include"player.h"

Star::Star()
{
   setPixmap(QPixmap(":/images/star.png"));
   setZValue(-1);
   timer= new QTimer;
}

void Star::start()
{
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

void Star::walk(int direc)
{
    Up(300);
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


void Star::Up(int distance)
{

    AirState=1;
    qreal curPosY= y();
    yAnimationUp->stop();
    yAnimationUp->setStartValue(curPosY);
    yAnimationUp->setEndValue(curPosY - distance);
    yAnimationUp->setEasingCurve(QEasingCurve::OutQuint);
    yAnimationUp->setDuration(distance);
    yAnimationUp->start();

}
//******************************   --Collision Detection --  ******************************************

QString Star::collideX()
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
            player->fastState();
            return "player";

        }
    }
    return "notcolliding";
}
//-------------------------------------------------------------------------------------
QString Star::collideY()
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

qreal Star::y() const
{
    return m_y;
}
//-------------------------------------------------------------------------------------
qreal Star::x() const
{
    return m_x;
}
//-------------------------------------------------------------------------------------
void Star::setY(qreal y)
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
void Star::setX(qreal x)
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
