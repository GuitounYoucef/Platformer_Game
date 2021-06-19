#include "koopa.h"

Koopa::Koopa(int x,int y)
{
    SpriteImageWalkLeft= new QPixmap(QPixmap(":/images/koopaWalkleft.png"));
    SpriteImageWalkRight= new QPixmap(QPixmap(":/images/koopaWalkRight.png"));
    setX(x);
    setY(y);
    width=106;
    height=120;
    frameNumber=5;
    start(200);
}
