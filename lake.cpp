#include "lake.h"
#include "water.h"

Lake::Lake(int xpos,int ypos,int width)
{
    Lakewidth=width/64;
    setZValue(-3);
    for(int i=0;i<=Lakewidth;i++)
    {

    Water *water = new Water(xpos+(i*30),ypos);
    addToGroup(water);
    }

}


