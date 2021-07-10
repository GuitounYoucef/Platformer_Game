#include "briks.h"
#include<QRandomGenerator>

Briks::Briks(int brikSize)
{
    switch (brikSize) {
    case 0:{
          setPixmap(QPixmap(":/images/oneBrick.png"));
        break;}
    case 1:{
          setPixmap(QPixmap(":/images/semiBrick.png"));
        }
        break;
    }

angle=(angle+(QRandomGenerator::global()->generate()) %45);
timer = new QTimer();
connect(timer, &QTimer::timeout, this, &Briks::rotate);
timer->start(50);
setZValue(-5);
}

qreal Briks::y() const
{
    return m_y;
}

qreal Briks::x() const
{
    return m_x;
}

void Briks::rotate()
{

    angle=angle+45;
    setRotation(angle);
}

void Briks::setY(qreal y)
{
    m_y = y;
    setPos(x(),m_y);
}

void Briks::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
}


