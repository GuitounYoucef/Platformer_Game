#include "pipe.h"

Pipe::Pipe(int pipeType)
{
    GraphicsPipe = new QGraphicsPixmapItem(QPixmap(":/images/pipe.png"));
    GraphicsPipe->setZValue(-1);
    addToGroup(GraphicsPipe);
    if (pipeType==2){
     piranha= new Piranha();
     piranha->setPos(x()+20,y()-50);
     addToGroup(piranha);
    }
}
