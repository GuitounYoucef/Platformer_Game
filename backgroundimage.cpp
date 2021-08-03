#include "backgroundimage.h"

BackgroundImage::BackgroundImage(QObject *parent) : QObject(parent)
{

setImageFile(":/images/BackgroundImage.png");
setZValue(-12);
}

void BackgroundImage::setImageFile(QString filePath)
{
setPixmap(QPixmap(filePath));
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
