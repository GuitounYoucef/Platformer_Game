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
yAnimationDown->setDuration(abs(distance));
yAnimationDown->start();
connect(yAnimationDown,&QPropertyAnimation::finished,[=](){
    frameTimer=80;

});
}

void Walkers::stopFalling()
{
 yAnimationDown->stop();
}
