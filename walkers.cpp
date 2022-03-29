#include "walkers.h"

#include "platform.h"

Walkers::Walkers()
{
    yAnimationUp = new QPropertyAnimation(this,"y",this);
    yAnimationDown = new QPropertyAnimation(this,"y",this);
    xAnimation= new QPropertyAnimation(this,"x",this);
}



void Walkers::fall(int distance, int startValue, int groundPosition)
{
AirState=2;
yAnimationDown->stop();
yAnimationDown->setStartValue(startValue);
yAnimationDown->setEndValue(groundPosition);
yAnimationDown->setEasingCurve(QEasingCurve::Linear);
yAnimationDown->setDuration(abs(distance/2));
yAnimationDown->start();
connect(yAnimationDown,&QPropertyAnimation::finished,[=](){
    frameTimer=80;
    if (!colided)
        outMap=true;
});
}

void Walkers::stopFalling()
{
    yAnimationDown->stop();
}

void Walkers::quitMap(int ypos)
{
    yAnimationUp->setStartValue(ypos);
    yAnimationUp->setEndValue(ypos-200);
    yAnimationUp->setEasingCurve(QEasingCurve::OutQuad);
    yAnimationUp->setDuration(400);

    yAnimationUp->start();
    connect(yAnimationUp,&QPropertyAnimation::finished,[=](){
        fall(1000, ypos-200, 500);
    });
}
