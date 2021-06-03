#ifndef PIPE_H
#define PIPE_H

#include <QObject>
#include<QGraphicsItemGroup>
#include"piranha.h"
#include"inanimateobject.h"

class Pipe : public InanimateObject
{
    Q_OBJECT
public:
    explicit Pipe(int pipeType);

signals:


private:
    QGraphicsItem *GraphicsPipe;
    Piranha *piranha;
};

#endif // PIPE_H
