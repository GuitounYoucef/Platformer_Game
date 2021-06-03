#include "piranha.h"

Piranha::Piranha()
{
    currentFrame = 0;
    spriteImageCoin= new QPixmap(QPixmap(":/images/piranha2.png"));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Piranha::nextFrame);
      timer->start(200);
      setZValue(-2);

    yAnimationUp= new QPropertyAnimation(this,"y",this);
    yAnimationDown= new QPropertyAnimation(this,"y",this);
    timerYanimation = new QTimer();
    timerYanimation->start(6000);
    connect(timerYanimation, &QTimer::timeout, this,[=](){
    yAnimationUp->setStartValue(y());
    yAnimationUp->setEndValue(y()-130);
    yAnimationUp->setDuration(3000);
    yAnimationUp->setEasingCurve(QEasingCurve::OutQuint);
    yAnimationUp->start();
    connect(yAnimationUp,&QPropertyAnimation::finished,[=](){
        yAnimationDown->setStartValue(y());
        yAnimationDown->setEndValue(y()+130);
        yAnimationDown->setDuration(3000);
        yAnimationDown->start();
    });
     });


}

qreal Piranha::y() const
{
    return m_y;
}

void Piranha::setY(qreal y)
{
    m_y = y;
    setPos(x(),m_y);
}

void Piranha::nextFrame()
{
    currentFrame=currentFrame+120;
if (currentFrame>750)
    currentFrame=0;
 update(0,0,120,169);
}

QPainterPath Piranha::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 120, 169);
    return path;
}

void Piranha::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0, *spriteImageCoin, currentFrame, 0, 120,169);
}

QRectF Piranha::boundingRect() const
{
    return QRectF(0,0,120,169);
}
