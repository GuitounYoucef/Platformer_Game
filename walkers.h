#ifndef WALKERS_H
#define WALKERS_H
#include <QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include<QTimer>
#include <QObject>


class Walkers: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Walkers();

    void fall(int distance, int startValue, int groundPosition);
    void stopFalling();

    QPropertyAnimation * yAnimationUp;
    QPropertyAnimation * yAnimationDown;
    QPropertyAnimation * xAnimation;
    int AirState=0;
    int groundState=0;  //1: walk right 2:walk left 0:stoping
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
    int line;
    int spriteColumn;
    int frameTimer=80;
    int frameDirection=1;
    int direction=0;

};

#endif // WALKERS_H
