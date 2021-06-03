#include "coin.h"

Coin::Coin(int x,int y)
{
    currentFrame = 0;
    spriteImageCoin= new QPixmap(QPixmap(":/images/coin.png"));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Coin::nextFrame);
      timer->start(150);
      setPos(x,y);
    coinSound=new QMediaPlayer();
    coinSound->setMedia(QUrl("qrc:/sound/sound/Coin.wav"));
}

void Coin::taken()
{
  coinSound->play();
  delete this;
}

void Coin::nextFrame()
{

currentFrame=currentFrame+51;
if (currentFrame>450)
    currentFrame=0;
 update(0,0,50,55);
}

QPainterPath Coin::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 50, 55);
    return path;
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0, *spriteImageCoin, currentFrame, 0, 50,55);
}

QRectF Coin::boundingRect() const
{
    return QRectF(0,0,50,55);
}
