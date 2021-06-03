#include "brickblock.h"

BrickBlock::BrickBlock(QObject *parent) : QObject(parent)
{
setPixmap(QPixmap(":/images/Bricks.png"));
}
