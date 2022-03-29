#ifndef WALKERS_H
#define WALKERS_H

#include<QPropertyAnimation>
#include<QTimer>
#include <QObject>


class Walkers: public QObject
{

public:
    explicit Walkers();

    void fall(int distance, int startValue, int groundPosition);
    void stopFalling();
    void quitMap(int ypos);

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
    bool colided=true;
    bool outMap=false;
signals:


};

#endif // WALKERS_H
