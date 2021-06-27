#include "goomba.h"
#include "platform.h"
#include<QDebug>

Goomba::Goomba(int x,int y)
{
    SpriteImageWalkLeft= new QPixmap(QPixmap(":/images/goombaWalkLeft.png"));
    SpriteImageWalkRight= new QPixmap(QPixmap(":/images/goombaWalkRight.png"));

    setX(x);
    setY(y);
    width=121;
    height=97;
    frameNumber=14;
    start(150);

}
