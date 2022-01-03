#ifndef GOOMBA_H
#define GOOMBA_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>

#include"enemy.h"


class Goomba :public Enemy
{


public:
    explicit Goomba(int x,int y);



public slots:
    QString collideX();

    signals:

private:








};

#endif // GOOMBA_H
