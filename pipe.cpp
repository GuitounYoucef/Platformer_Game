#include "pipe.h"

Pipe::Pipe(int pipeType)
{
    GraphicsPipe = new QGraphicsPixmapItem(QPixmap(":/images/pipe.png"));
    GraphicsPipe->setZValue(-1);
    addToGroup(GraphicsPipe);
    if (pipeType==2){
     piranha= new Piranha();
     piranha->setX(x()+20);
     piranha->setY(y());
     addToGroup(piranha);
    }
}
