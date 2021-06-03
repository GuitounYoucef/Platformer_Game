#include "backgroundimage.h"

BackgroundImage::BackgroundImage(QObject *parent) : QObject(parent)
{
setPixmap(QPixmap(":/images/BackgroundImage.png"));
setZValue(-12);
}

qreal BackgroundImage::x() const
{
    return m_x;
}

void BackgroundImage::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
}
