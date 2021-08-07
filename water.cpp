#include "water.h"
#include<QRandomGenerator>

Water::Water(int xpos,int ypos)
{

    setPixmap(QPixmap(":/images/water.png"));
   setOpacity(0.95);
    timer = new QTimer();
    setPos(xpos,ypos);
    length= (QRandomGenerator::global()->generate()) %20;
    if (length%2==0)
    right=true;
    else right=false;
    xAnimation= new QPropertyAnimation(this,"x",this);
    xAnimation->setStartValue(xpos);
    xAnimation->setEndValue(xpos-length);
    xAnimation->setDuration(3000);
    xAnimation->start();
    connect(xAnimation,&QPropertyAnimation::finished,[=](){
      if (right)
      {
          xAnimation->setStartValue(xpos-length);
          xAnimation->setEndValue(xpos);
          xAnimation->setEasingCurve(QEasingCurve::Linear);
          right=false;

      }
      else
      {
          xAnimation->setStartValue(xpos);
          xAnimation->setEndValue(xpos-length);
          xAnimation->setEasingCurve(QEasingCurve::Linear);
          right=true;
      }


      xAnimation->start();
    });


}

void Water::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
}


