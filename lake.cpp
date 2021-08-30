#include "lake.h"
#include "water.h"

Lake::Lake(int xpos,int ypos,int width)
{
    Lakewidth=width/64;
    setZValue(-3);

    Water *water = new Water(xpos+(i*30),ypos-20);
    addToGroup(water);


}


