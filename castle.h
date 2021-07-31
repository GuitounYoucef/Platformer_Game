#ifndef CASTLE_H
#define CASTLE_H

#include<QGraphicsItemGroup>
#include"inanimateobject.h"
#include "halfcastleright.h"
class Castle: public InanimateObject
{
public:
    Castle(int xpos,int ypos,int part);
    int Part;

};

#endif // CASTLE_H
