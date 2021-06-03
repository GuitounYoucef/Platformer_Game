#include "cloud.h"

Cloud::Cloud(int xAxe,int yAxe )
{
setPixmap(QPixmap(":/images/big-cloud.png"));
setZValue(-12);
setX(xAxe);
setY(yAxe);
xAnimation= new QPropertyAnimation(this,"x",this);
xAnimation->setStartValue(x());
xAnimation->setEndValue(x()-5000);
xAnimation->setDuration(260000);
xAnimation->setEasingCurve(QEasingCurve::Linear);
xAnimation->start();
}

qreal Cloud::x() const
{
    return m_x;
}

qreal Cloud::y() const
{
    return m_y;
}

void Cloud::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
}

void Cloud::setY(qreal y)
{
    m_y = y;
}
