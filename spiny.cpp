#include "spiny.h"

Spiny::Spiny(int x,int y)
{
    SpriteImageWalkLeft= new QPixmap(QPixmap(":/images/spinyWalkLeft.png"));
    SpriteImageWalkRight= new QPixmap(QPixmap(":/images/spinyWalkRight.png"));
    SpriteImageWalkLeftDie= new QPixmap(QPixmap(":/images/spinyWalkLeft.png"));
    SpriteImageWalkRightDie= new QPixmap(QPixmap(":/images/spinyWalkRight.png"));
    DieSound=new QMediaPlayer();
    DieSound->setMedia(QUrl("qrc:/sound/sound/Squish.wav"));
    setX(x);
    setY(y);
    width=159;
    height=120;
    frameNumber=30;
    start(20);
}
