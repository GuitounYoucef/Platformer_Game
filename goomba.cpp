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
    speed=2;
}

QString Goomba::collideX()
{
    qreal t;
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        InanimateObject * inanimateObject =dynamic_cast<InanimateObject*>(item);

        if ((platform))
        {

            t=this->y();
            if ((item->y()<t) )
              if (((direction==0) && (item->x()>=this->x())) || ((direction==1) && (item->x()<=this->x())) )
                    return "collide";
        }
        else
            if (inanimateObject)
            {
                t=this->y();
                if ((inanimateObject->y()<t) )
                    if (((direction==0) && (inanimateObject->x()>=this->x())) || ((direction==1) && (inanimateObject->x()<=this->x())) )
                        return "collide";

            }

    }
    return "notcolliding";
}
