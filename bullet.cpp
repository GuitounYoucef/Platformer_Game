#include "bullet.h"

Bullet::Bullet(int x,int direction)
{
   setRect(0,0,10,10);
   xAnimation= new QPropertyAnimation(this,"x",this);
   xAnimation->setStartValue(x);
   if (direction==0)
   xAnimation->setEndValue(660);
   else xAnimation->setEndValue(-660);
   xAnimation->setEasingCurve(QEasingCurve::Linear);
   xAnimation->setDuration(2000);
   connect(xAnimation, &QPropertyAnimation::finished ,[=](){
       delete this;

   });

   xAnimation->start();

}

void Bullet::move()
{

}
