#ifndef BRICKBLOCK_H
#define BRICKBLOCK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include"platform.h"

class BrickBlock : public Platform
{
    Q_OBJECT
public:
    explicit BrickBlock(QObject *parent = nullptr);

signals:

};

#endif // BRICKBLOCK_H
