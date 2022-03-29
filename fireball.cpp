#include "fireball.h"
#include "enemy.h"
#include "piranha.h"

Fireball::Fireball(qreal x,qreal y,int direction)
{
   xdirec=direction;
   currentFrame = 0;
   framedirection=1;
   spriteImageFireRight= new QPixmap(QPixmap(":/images/fireballRight.png"));
   spriteImageFireLeft= new QPixmap(QPixmap(":/images/fireballLeft.png"));



   setX(x);
   setY(y-20);
   framesTimer = new QTimer();
   connect(framesTimer, &QTimer::timeout, this, &Fireball::nextFrame);     
   framesTimer->start(100);

   xAnimation= new QPropertyAnimation(this,"x",this);
   upAnimation= new QPropertyAnimation(this,"y",this);
   fallAnimation= new QPropertyAnimation(this,"y",this);
   moveAnimation= new QParallelAnimationGroup();
   UpFallSeqAnimation=new QSequentialAnimationGroup();

   UpFallSeqAnimation->addAnimation(upAnimation);
   UpFallSeqAnimation->addAnimation(fallAnimation);

   moveAnimation->addAnimation(UpFallSeqAnimation);
   moveAnimation->addAnimation(xAnimation);
   startMoveAnimation();

   connect(xAnimation, &QPropertyAnimation::finished ,[=](){
       delete this;
   });


}

void Fireball::startMoveAnimation()
{
    moveAnimation->stop();
    upAnimation->stop();
    fallAnimation->stop();
    UpFallSeqAnimation->stop();
    xAnimation->stop();

    xAnimation->setStartValue(x());
    if (xdirec==0)
    xAnimation->setEndValue(x()+1800);
    else xAnimation->setEndValue(x()-1800);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(2000);


    upAnimation->setStartValue(y());
    upAnimation->setEndValue(y()-ydirec);
    upAnimation->setEasingCurve(QEasingCurve::OutQuad);
    upAnimation->setDuration(200);



    fallAnimation->setStartValue(y()-ydirec);
    fallAnimation->setEndValue(y()+1000);
    fallAnimation->setEasingCurve(QEasingCurve::OutQuad);
    fallAnimation->setDuration(3000);

    moveAnimation->start();
}

bool Fireball::collideY()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);

        if ((platform))
        {
            if(this->y()+45>item->y())
            {

               return true;

            }
        }

    }
    return false;
}

bool Fireball::collideX()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        Enemy * enemy =dynamic_cast<Enemy*>(item);
        Piranha * piranha =dynamic_cast<Piranha*>(item);
        if ((platform))
        {
            if((this->x()+20>item->x()) && (this->y()>item->y()))
            {

               return true;

            }
        }
        if (enemy)
        {
            enemy->die();
            delete this;
        }
        if(piranha)
        {
            piranha->die();
            delete this;
        }
    }
    return false;
}



qreal Fireball::y() const
{
    return m_y;
}

qreal Fireball::x() const
{
    return m_x;

}

void Fireball::setY(qreal y)
{
    m_y = y;
    setPos(x(),m_y);
    if (collideX())
        delete this;
    if (collideY())
    {

        m_y=m_y-15;
        steps=--steps;
        if (steps<=0)
            delete this;

      //  ydirec=ydirec*(steps*2)/10;

        startMoveAnimation();
    //    collideTimer->start(ydirec);




    }


}

void Fireball::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
    if (collideX())
        delete this;
}


void Fireball::nextFrame()
{

    if (framedirection==1)
        currentFrame=currentFrame+128;
    else currentFrame=currentFrame-128;
    if ((currentFrame>=384)&&(framedirection==1))
    {
        framedirection=-1;

    }
    else
        if ((currentFrame<=0)&&(framedirection==-1))
        {
            framedirection=1;
        }

 update(0,0,128,64);



}
QPainterPath Fireball::shape() const
{
    QPainterPath path;
    path.addRect(0,0,128,64);

    return path;
}

void Fireball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (xdirec==0)
    painter->drawPixmap(0,0, *spriteImageFireRight, currentFrame,0, 128,64);
    else painter->drawPixmap(0,0, *spriteImageFireLeft, currentFrame,0, 128,64);
}

QRectF Fireball::boundingRect() const
{
    return QRectF(0,10,128,64);
}

