#include "water.h"
#include<QRandomGenerator>

Water::Water(int xpos,int ypos)
{
    currentFrame = 0;
    spriteImageWater= new QPixmap(QPixmap(":/images/water2.png"));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Water::nextFrame);
      timer->start(80);
      setPos(xpos,ypos);

}



void Water::nextFrame()
{

currentFrame=currentFrame+2;
if (currentFrame>=64)
    currentFrame=0;
 update(0,0,128, 114);
}

QPainterPath Water::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 128, 114);
    return path;
}

void Water::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0, *spriteImageWater, currentFrame, 0, 128, 114);
}

QRectF Water::boundingRect() const
{
    return QRectF(0,0,128, 114);
}
