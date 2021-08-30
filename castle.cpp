#include "castle.h"
#include "platform.h"

Castle::Castle(int xpos,int ypos,int part)
{
    Part=part;


    switch (part) {
    case 1:{
        QGraphicsPixmapItem *HalfCastle1 = new QGraphicsPixmapItem(QPixmap(":/images/halfcastle1.png"));
        addToGroup(HalfCastle1);
        setZValue(-2);
        setPos(xpos,ypos-360);
        break;
    }
    case 2:{
        QGraphicsPixmapItem *HalfCastle1 = new QGraphicsPixmapItem(QPixmap(":/images/halfcastle2.png"));
        HalfCastle1->setX(xpos+209);
        HalfCastle1->setY(ypos-360);
        //setOpacity(0.5);
        setZValue(10);
        addToGroup(HalfCastle1);
        break;
    }

}

}
