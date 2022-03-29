#include "enemy.h"
#include "player.h"

Enemy::Enemy()
{

}
void Enemy::start(int frametime)
{
    currentFrame = 0;
    setZValue(5);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::nextFrame);
    timer->start(frametime);
    groundState=2;
    fall(2000,y(),500);

    dieTimer = new QTimer();

}

void Enemy::die()
{
    height=height/3;
    helth=0;

    *SpriteImageWalkRight=SpriteImageWalkRightDie->scaled(frameNumber*width, height, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);
    *SpriteImageWalkLeft=SpriteImageWalkLeftDie->scaled(frameNumber*width, height, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);
     setY(y()+height*2+10);
     timer->stop();
     xAnimation->stop();

    connect(dieTimer, &QTimer::timeout, this, [=]{

        DieSound->play();
        delete this;
    });
    dieTimer->start(150);

}
void Enemy::nextFrame()
{
    if (groundState==2)
    {
        currentFrame=currentFrame+width;
        if (currentFrame>width*(frameNumber-1))
            currentFrame=0;
    }
    else
    {
        currentFrame=currentFrame-width;
        if (currentFrame==0)
            currentFrame=width*(frameNumber-1);
    }
    //if (Heightsize<height)





    update(0,0,width,height);
}

QPainterPath Enemy::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, width,height);
    return path;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (groundState==2)
    painter->drawPixmap(0,0, *SpriteImageWalkLeft, currentFrame, 0, width,height+20);
    else
    painter->drawPixmap(0,0, *SpriteImageWalkRight, currentFrame, 0, width,height+20);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(0,0,width,height+20);
}

void Enemy::walk()
{
    xAnimation->stop();
    xAnimation->setStartValue(x());
    if (groundState==1)
        xAnimation->setEndValue(x()+400*speed);
    else xAnimation->setEndValue(x()-400*speed);
    xAnimation->setDuration(4000/speed);
    //xAnimation->setEasingCurve(QEasingCurve::OutSine);
    xAnimation->setEasingCurve(QEasingCurve::Linear);

    AirState=0;
    xAnimation->start();
}

qreal Enemy::x() const
{
 return m_x;
}

qreal Enemy::y() const
{
    return m_y;
}



void Enemy::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
  //  qDebug()<<xAnimation->currentTime();

    if ((xAnimation->currentTime() >=4000/speed) || collideX()=="platform")
      {
       if (groundState==1)
           groundState=2;
       else groundState=1;
       walk();
       }
        if ((collideY()=="notcolliding")&&(colided))
        {
            if (AirState==0)
                fall(1000+y(),y(),500);
        }
     else
      if ((collideX()=="die") &&(helth>0))
          die();
}

void Enemy::setY(qreal y)
{
    m_y = y;

    if (collideY()!="notcolliding") // colliding
    {

        if ((collideY()=="foots") && (AirState==2) &&(colided))
        {
            stopFalling();
            walk();
            //m_y=y-20;
            if (AirState!=0)
                AirState=0;
        }
    }
    setPos(x(),m_y);
}

//-------------------------------------------------------------------------------------
QString Enemy::collideY()
{
 if (colided)
  {

    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        if ((platform) && (AirState!=-1) && (colided))
        {
            //qDebug()<<"Goomba collide";
                  if ((platform->getPlatformType()!=-1) || (platform->getPlatformType()!=4))
                    return "foots";
        }
    }
 }
    return "notcolliding";
}

QString Enemy::collideX()
{
if (colided)
{
    qreal t;
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {


        Player * player =dynamic_cast<Player*>(item);
        if (player)
        {
          if(((player->y()+player->playerHeight/2<this->y()) &&(player->helth>0)) || (player->helth==4))
          {
              player->AirState=0;
              player->Up(200);
              player->Down();
              return "die";
          }
          else
          {
          player->quitMap(player->y());
          return "plyer";
          }
        }
//        }
    }
}
    return "notcolliding";
}
