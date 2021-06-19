#include "spiny.h"

Spiny::Spiny(int x,int y)
{
    SpriteImageWalkLeft= new QPixmap(QPixmap(":/images/spinyWalkLeft.png"));
    SpriteImageWalkRight= new QPixmap(QPixmap(":/images/spinyWalkRight.png"));
    setX(x);
    setY(y);
    width=159;
    height=120;
    frameNumber=30;
    start(20);
}
