#include "halfcastleright.h"

HalfCastleRight::HalfCastleRight(int xpos,int ypos)
{
    setPixmap(QPixmap(":/images/halfcastle2.png"));
    setZValue(10);
    setPos(xpos,ypos-325);
}
