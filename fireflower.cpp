#include "fireflower.h"

Fireflower::Fireflower()
{
   setPixmap(QPixmap(":/images/FireFlower.png"));
   setZValue(-1);
   yAnimationUp = new QPropertyAnimation(this,"y",this);

}
void Fireflower::start()
{
    yAnimationUp->stop();
    yAnimationUp->setStartValue(y());
    yAnimationUp->setEndValue(y()-65);
    yAnimationUp->setDuration(1000);
    yAnimationUp->setEasingCurve(QEasingCurve::Linear);
    yAnimationUp->start();
}
void Fireflower::taken()
{
  //coinSound->play();
  delete this;
}

qreal Fireflower::y() const
{
    return m_y;
}

qreal Fireflower::x() const
{
    return m_x;
}

void Fireflower::setY(qreal y)
{
    m_y = y;
    setPos(x(),m_y);
}

void Fireflower::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
}
