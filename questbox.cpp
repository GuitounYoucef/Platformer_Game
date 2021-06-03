#include "questbox.h"

Questbox::Questbox()
{
    currentFrame = 0;
    spriteImageCoin= new QPixmap(QPixmap(":/images/questbox.png"));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Questbox::nextFrame);
      timer->start(80);

}

void Questbox::nextFrame()
{
currentFrame=currentFrame+64;
if (currentFrame>960)
    currentFrame=0;
 update(0,0,64,64);
}

QPainterPath Questbox::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 64, 64);
    return path;
}

void Questbox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0, *spriteImageCoin, currentFrame, 0, 64,64);
}

QRectF Questbox::boundingRect() const
{
    return QRectF(0,0,64,64);
}
