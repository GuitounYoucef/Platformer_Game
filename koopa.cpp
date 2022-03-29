#include "koopa.h"
#include "goomba.h"



Koopa::Koopa(int x,int y)
{
    SpriteImageWalkLeft= new QPixmap(QPixmap(":/images/koopaWalkleft.png"));
    SpriteImageWalkRight= new QPixmap(QPixmap(":/images/koopaWalkRight.png"));
    SpriteImageShell= new QPixmap(QPixmap(":/images/koopaShell.png"));
    setX(x);
    setY(y);
    width=192;
    height=160;
    frameNumber=16;
    currentFrame = 0;
    setZValue(15);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Koopa::nextFrame);
    timer->start(frametime);
    groundState=2;
    AirState=0;
    fall(2000,y,500);
    changeStateTimer = new QTimer();
    connect(changeStateTimer, &QTimer::timeout, this, &Koopa::setKoopastate);
}

Koopa::~Koopa()
{

}

void Koopa::setKoopastate()
{
    koopaState=2;
    qDebug()<<"koopaState :: "<<koopaState;
}

void Koopa::hit()
{
    switch (koopaState) {
    case 1:{
        koopaState=2;
        spriteState=0;
        frameNumber=15;
        frametime=20;
        height=145;
        timer->stop();
        currentFrame = 15;
        xAnimation->stop();
        break;
    }
    case 2:{
        timer->start(frametime);
        koopaState=3;
        speed=2;
        walk();
        break;
    }
    case 3:{
        if((xAnimation->duration()<2500)&&(xAnimation->duration()>0))
        {
        koopaState=2;
        changeStateTimer->start(200);
        spriteState=0;
        timer->stop();
        xAnimation->stop();
        }
        break;
    }
    }
}

void Koopa::nextFrame()
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

QPainterPath Koopa::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, width,height);
    return path;
}

void Koopa::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    switch (spriteState) {
    case -1: case 0:{
        painter->drawPixmap(0,0, *SpriteImageShell, currentFrame, 0, width,height+20);
           break;}
    case 1:{
        if (groundState==2)
            painter->drawPixmap(0,0, *SpriteImageWalkLeft, currentFrame, 0, width,height+20);
        else
            painter->drawPixmap(0,0, *SpriteImageWalkRight, currentFrame, 0, width,height+20);
           break;}
    }

}

QRectF Koopa::boundingRect() const
{
    return QRectF(0,0,width,height+20);
}


void Koopa::walk()
{
    xAnimation->stop();
    xAnimation->setStartValue(x());
    if (groundState==1)
        xAnimation->setEndValue(x()+600*speed);
    else xAnimation->setEndValue(x()-600*speed);
    xAnimation->setDuration(3000/speed);
    //xAnimation->setEasingCurve(QEasingCurve::OutSine);
    xAnimation->setEasingCurve(QEasingCurve::Linear);

    AirState=0;
    xAnimation->start();
    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        if(koopaState==3)
            walk();
    });
}

qreal Koopa::x() const
{
 return m_x;
}

qreal Koopa::y() const
{
    return m_y;
}



void Koopa::setX(qreal x)
{
    m_x = x;
    setPos(m_x,y());
  //  qDebug()<<xAnimation->currentTime();

    if ((xAnimation->currentTime() >=3000/speed) || collideX()=="platform")
      {
       if (groundState==1)
           groundState=2;
       else groundState=1;
       walk();
       }
        if ((collideY()=="notcolliding")&&(colided))
        {
            if (AirState==0)
                fall(1000-y(),y(),500);
        }
     else
      if (collideX()=="hited")
          hit();

}

void Koopa::setY(qreal y)
{
    m_y = y;

    if (collideY()!="notcolliding") // colliding
    {

        if ((collideY()=="foots") && (AirState==2))
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
QString Koopa::collideY()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        if ((platform) && (AirState!=-1))
        {
            //qDebug()<<"Goomba collide";
                  if ((platform->getPlatformType()!=-1) || (platform->getPlatformType()!=4))
                    return "foots";
        }
    }
    return "notcolliding";
}

QString Koopa::collideX()
{
    qreal t;
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {

        Player * player =dynamic_cast<Player*>(item);
        Goomba * goomba =dynamic_cast<Goomba*>(item);
        if ((goomba) && (goomba->colided) &&(koopaState==3))
        {
        goomba->colided=false;
       // goomba->setRotation(180);
        goomba->quitMap(goomba->y());
        return "goomba";
        }
        else
        if ((player) &&(player->colided))
        {
          if(((player->y()+player->playerHeight/2<this->y()) &&(player->helth>0)) || (player->helth==4) )
          {
              player->AirState=0;
              player->Up(200);
              player->Down();
              return "hited";
          }
          else
          {
          player->colided=false;
          player->DieSound->play();
          player->quitMap(player->y());
          return "player";
          }
        }
    }
    return "notcolliding";
}
