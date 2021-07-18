#include "goomba.h"
#include "platform.h"
#include<QDebug>

Goomba::Goomba(int x,int y)
{
    SpriteImageWalkLeft= new QPixmap(QPixmap(":/images/goombaWalkLeft.png"));
    SpriteImageWalkRight= new QPixmap(QPixmap(":/images/goombaWalkRight.png"));
    SpriteImageWalkLeftDie= new QPixmap(QPixmap(":/images/goombaWalkLeft.png"));
    SpriteImageWalkRightDie= new QPixmap(QPixmap(":/images/goombaWalkRight.png"));
    DieSound=new QMediaPlayer();
    DieSound->setMedia(QUrl("qrc:/sound/sound/Squish.wav"));
    setX(x);
    setY(y);
    width=121;
    height=97;
    frameNumber=14;
    start(150);


}
