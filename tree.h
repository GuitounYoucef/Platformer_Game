#ifndef TREE_H
#define TREE_H

#include <QObject>
#include<QGraphicsPixmapItem>

class Tree : public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tree(int xpos);

signals:

};

#endif // TREE_H
