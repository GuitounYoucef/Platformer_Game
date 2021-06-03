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

int x = (QRandomGenerator::global()->generate()) %360;
setRotation(x);
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
