#include "goomba.h"
#include "platform.h"
#include<QDebug>

Goomba::Goomba()
{
    currentFrame = 0;
    spriteImageGoomba= new QPixmap(QPixmap(":/images/goomba.png"));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Goomba::nextFrame);
      timer->start(150);


    fall(3000,y(),500);
   // walk(2);

}
void Goomba::nextFrame()
{

currentFrame=currentFrame+121;
if (currentFrame>1600)
    currentFrame=0;
 update(0,0,121,97);
}

QPainterPath Goomba::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 121,97);
    return path;
}

void Goomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0, *spriteImageGoomba, currentFrame, 0, 121,97);
}

QRectF Goomba::boundingRect() const
{
    return QRectF(0,0,121,97);
}

void Goomba::walk(int direc)
{
    xAnimation->stop();
    xAnimation->setStartValue(x());
    if (direc==1)
        xAnimation->setEndValue(x()+700);
    else xAnimation->setEndValue(x()-700);
    xAnimation->setDuration(8000);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    groundState=direc;
    AirState=0;
    xAnimation->start();
}

qreal Goomba::x() const
{
 return m_x;
}

qreal Goomba::y() const
{
 return m_y;
}

void Goomba::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());

        if (collideY()=="notcolliding")
        {
            if (AirState==0)
                fall(1000-y(),y(),500);

        }

}

void Goomba::setY(qreal y)
{
    m_y = y;
    qDebug()<<"Goomba collide **";
    if (collideY()!="notcolliding") // colliding
    {

        if ((collideY()=="foots") && (AirState==2))
        {
            stopFalling();
            walk(2);
            m_y=y-10;
            if (AirState!=0)
                AirState=0;
        }
    }
    setPos(x(),m_y);
}



//-------------------------------------------------------------------------------------
QString Goomba::collideY()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        if ((platform) && (AirState!=-1))
        {
            qDebug()<<"Goomba collide";
                  if ((platform->getPlatformType()!=-1) || (platform->getPlatformType()!=4))
                    return "foots";
        }
    }
    return "notcolliding";
}

//******************************    --Positioning--      *********************************


