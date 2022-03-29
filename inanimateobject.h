#ifndef INANIMATEOBJECT_H
#define INANIMATEOBJECT_H

#include <QObject>
#include<QGraphicsPixmapItem>
class InanimateObject: public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    InanimateObject();
    void deleteObj();
};

#endif // INANIMATEOBJECT_H
