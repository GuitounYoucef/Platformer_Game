#include "player.h"
#include<QGraphicsView>
#include<QGraphicsEffect>
#include<QColor>
#include"platform.h"
#include"inanimateobject.h"
#include"coin.h"
#include<QDebug>
#include <QScrollBar>
#include<QParallelAnimationGroup>
#include<QEventLoop>


#include"castle.h"
#include"endstage.h"
#include "lake.h"
#include "fireflower.h"




Player::Player(QGraphicsView *graphicsView,QGraphicsScene *scenePlayer,BackgroundImage *background)
{
    QGraphicsLineItem *line1=new QGraphicsLineItem;
    line1->setLine(x(),y(),x()+100,y());

    currentFrame = 0;
    spriteImageBigMario = new QPixmap(QPixmap(":/images/BigMarioSprite.png"));
    spriteImageSmallMario = new QPixmap(QPixmap(":/images/mario-sprite-png.png"));
    // Fire Mario Sprite sheet
    //Walk
    spriteImageFireMarioWalkRight = new QPixmap(QPixmap(":/images/MarioFireWalkRight.png"));
    spriteImageFireMarioWalkLeft = new QPixmap(QPixmap(":/images/MarioFireWalkLeft.png"));
    //Jump
    spriteImageFireMarioJumpRight = new QPixmap(QPixmap(":/images/MarioFireJumpRight.png"));
    spriteImageFireMarioJumpLeft = new QPixmap(QPixmap(":/images/MarioFireJumpLeft.png"));
    //Breath
    spriteImageFireMarioBreathRight = new QPixmap(QPixmap(":/images/MarioFireBreathRight.png"));
    spriteImageFireMarioBreathLeft = new QPixmap(QPixmap(":/images/MarioFireBreathLeft.png"));
    //Throw FireBall
    spriteImageFireMarioThrowBallRight = new QPixmap(QPixmap(":/images/MarioThrowFireBallRight.png"));
    spriteImageFireMarioThrowBallLeft = new QPixmap(QPixmap(":/images/MarioThrowFireBallLeft.png"));

    // Big Mario Sprite sheet
    //Walk
    spriteImageBigMarioWalkRight = new QPixmap(QPixmap(":/images/mariowalkright.png"));
    spriteImageBigMarioWalkLeft = new QPixmap(QPixmap(":/images/mariowalkleft.png"));
    //Jump
    spriteImageBigMarioJumpRight = new QPixmap(QPixmap(":/images/marioJumpRight.png"));
    spriteImageBigMarioJumpLeft = new QPixmap(QPixmap(":/images/marioJumpLeft.png"));
    //Breath
    spriteImageBigMarioBreathRight = new QPixmap(QPixmap(":/images/marioBreathright.png"));
    spriteImageBigMarioBreathLeft = new QPixmap(QPixmap(":/images/marioBreathleft.png"));
    // Big Mario Sprite sheet Fast
    //Walk
    spriteImageBigMarioWalkRightFast = new QPixmap(QPixmap(":/images/mariowalkrightFast.png"));
    spriteImageBigMarioWalkLeftFast = new QPixmap(QPixmap(":/images/mariowalkleftFast.png"));
    //Breath
    spriteImageBigMarioBreathRightFast = new QPixmap(QPixmap(":/images/marioBreathrightFast.png"));
    spriteImageBigMarioBreathLeftFast = new QPixmap(QPixmap(":/images/marioBreathleftFast.png"));

    // Small Mario Sprite sheet
    //Walk
    spriteImageSmallMarioWalkRight = new QPixmap(QPixmap(":/images/mariowalkright.png"));
    *spriteImageSmallMarioWalkRight =spriteImageBigMarioWalkRight->scaled(3072, 192, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);

    spriteImageSmallMarioWalkLeft = new QPixmap(QPixmap(":/images/mariowalkleft.png"));
    *spriteImageSmallMarioWalkLeft =spriteImageBigMarioWalkLeft->scaled(3072, 192, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);
    //Breath
    spriteImageSmallMarioBreathRight = new QPixmap(QPixmap(":/images/marioBreathright.png"));
    *spriteImageSmallMarioBreathRight =spriteImageBigMarioBreathRight->scaled(3072, 192, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);

    spriteImageSmallMarioBreathLeft = new QPixmap(QPixmap(":/images/marioBreathleft.png"));
    *spriteImageSmallMarioBreathLeft=spriteImageBigMarioBreathLeft->scaled(3072, 192, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);

    spriteImageSmallMarioJumpRight = new QPixmap(QPixmap(":/images/marioJumpRight.png"));
    *spriteImageSmallMarioJumpRight =spriteImageBigMarioJumpRight->scaled(3072, 192, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);

    spriteImageSmallMarioJumpLeft = new QPixmap(QPixmap(":/images/marioJumpLeft.png"));
    *spriteImageSmallMarioJumpLeft=spriteImageBigMarioJumpLeft->scaled(3072, 192, Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);
//==================================================================
    backgroundAnimation = new QPropertyAnimation(background,"x");
    imageXpos=background->x();
    backgroundimage=background;
    line=200;
    timerSmallMario = new QTimer();
    timerBigMario = new QTimer();
    fastTimer = new QTimer();
    timerMarioSize = new QTimer();
    shootTimer = new QTimer();
    connect(timerSmallMario, &QTimer::timeout, this, &Player::nextFrameSmallMario);
    connect(timerBigMario, &QTimer::timeout, this, &Player::nextFrameBigMario);
    timerBigMario->start(frameTimer);

    connect(timerMarioSize,&QTimer::timeout, this,&Player::sizeCycle);



    groundPosition=500;
    yPos=groundPosition;

    graphicsView->setScene(scenePlayer);
    viewWidth= 1900;

    xScrollPos=graphicsView->horizontalScrollBar();
    yScrollPos=graphicsView->verticalScrollBar();

    xScrollPos->setValue(x()-950);
    xScrollAnimation = new QPropertyAnimation(xScrollPos,"value");
    yScrollAnimationUp = new QPropertyAnimation(yScrollPos,"value");
    yScrollAnimationDown= new QPropertyAnimation(yScrollPos,"value");

    playerScroll = new QParallelAnimationGroup;
    playeryAxeScroll = new QParallelAnimationGroup;
    playeryAxeScrollDown = new QParallelAnimationGroup;

    playeryAxeScroll->addAnimation(yAnimationUp);
    playeryAxeScroll->addAnimation(yScrollAnimationUp);

    playeryAxeScrollDown->addAnimation(yAnimationDown);
    playeryAxeScrollDown->addAnimation(yScrollAnimationDown);

    playerScroll->addAnimation(xAnimation);
    playerScroll->addAnimation(xScrollAnimation);
    playerScroll->addAnimation(backgroundAnimation);

    jumpSound=new QMediaPlayer();
    jumpSound->setMedia(QUrl("qrc:/sound/sound/Jump.wav"));

    powerupSound=new QMediaPlayer();
    powerupSound->setMedia(QUrl("qrc:/sound/sound/Powerup.wav"));

    DieSound=new QMediaPlayer();
    DieSound->setMedia(QUrl("qrc:/sound/sound/Die.wav"));

    backgroundMusic=new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:/sound/sound/overworld.ogg"));
    backgroundMusic->setVolume(0);
   // backgroundMusic->play();
    setZValue(5);
    stopWalking();
    spriteSheetState=111;

    fireBallSound =new QMediaPlayer();
    fireBallSound->setMedia(QUrl("qrc:/sound/sound/Fire Ball.wav"));
    fall(groundPosition-y(),y(),groundPosition);




}

Player::~Player()
{
emit RetCheckPoint();
}


//******************************   --Movement--  ******************************************

void Player::addBullet()
{
    bullet = new Bullet(x(),direction);
    bullet->setPos(x()+40,y()+30);
    scene()->addItem(bullet);
    bullet->move();
}
//-------------------------------------------------------------------------------------
void Player::walk(int dirc,BackgroundImage *background)
{
    if (dirc==0)
    spriteSheetState=((spriteSheetState/10)*10)+1;        //**1
    else spriteSheetState=((spriteSheetState/10)*10)+2;   //**2

    frameTimer=60;
    direction=dirc;
    int step;
    int duration;
    xAnimation->stop();
    xScrollAnimation->stop();
    backgroundAnimation->stop();

    if (AirState==0)
    {
        step=1200;
        spriteColumn=4096*frameLength/256;
        spriteSheetState=((spriteSheetState/100)*100)+20+(spriteSheetState%10); //*2*
        qDebug()<<"spriteSheetState walk :: "<<spriteSheetState;

    }
    else
    {
        step=600;
    }
    duration=2100/speed;
    xAnimation->setStartValue(x());
    xScrollAnimation->setStartValue(xScrollPos->value());
    backgroundAnimation->setStartValue(background->x());
    if (direction==0)                   // 0:walk Right ; 1:walk Left
    {
        groundState=1;
        xAnimation->setEndValue(x()+step);
        xScrollAnimation->setEndValue(xScrollPos->value()+step);
        if(background->pixmap().width()+background->x()<scene()->width()-600)
            backgroundAnimation->setEndValue(background->x()+step-100);
        else
            backgroundAnimation->setEndValue(background->x());
    }
    else
    {
        groundState=2;
        xAnimation->setEndValue(x()-step);
        xScrollAnimation->setEndValue(xScrollPos->value()-step);
        if(background->x()>-950)
            backgroundAnimation->setEndValue(background->x()-step+100);
        else
            backgroundAnimation->setEndValue(background->x());
    }
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xScrollAnimation->setEasingCurve(QEasingCurve::Linear);
    backgroundAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(duration);
    xScrollAnimation->setDuration(duration);
    backgroundAnimation->setDuration(duration);
    if  (( ( x()-950 >(xScrollPos->value()+viewWidth/12) && (direction==0)  )
                          || (( (background->x() >=(x()-2000)  ) && (direction==1)))))
                            //direction :0=left  1=right
    {
        playerScroll->start();
        connect(playerScroll,&QPropertyAnimation::finished,[=](){
            groundState=0;
        });
    }
    else
    {
        xAnimation->start();
        connect(xAnimation,&QPropertyAnimation::finished,[=](){
            groundState=0;
        });
    }

}
//-------------------------------------------------------------------------------------
void Player::stopWalking()
{
 spriteSheetState=((spriteSheetState/100)*100)+10+(spriteSheetState%10);
 playerScroll->stop();
 xAnimation->stop();
 groundState=0;
 frameTimer=200;
 spriteColumn=4096*frameLength/256;
}



//-------------------------------------------------------------------------------------
void Player::die()
{
setY(-500);
backgroundMusic->setMedia(QUrl("qrc:/sound/sound/overworld.ogg"));
//if (helth>1)
  // helth=1;
setMarioSize(0);
frameLength=192;
//if(helth==0)
{

    stopWalking();
    stopFalling();
    colided=true;

    backgroundMusic->stop();
    emit RetCheckPoint();
    fall(groundPosition-y(),y(),groundPosition);
}
}
//-------------------------------------------------------------------------------------
void Player::Jump()
{
    UpinAir=false;


    spriteColumn=4096*frameLength/256;
    currentFrame=0;
    Up(playerHeight*3);
    Down();
}
//-------------------------------------------------------------------------------------
void Player::Up(int distance)
{


    frameTimer=5;
    if (AirState==0)
    {
        spriteSheetState=((spriteSheetState/100)*100)+30+(spriteSheetState%10);  //*3*
        qDebug()<<"spriteSheetState :: "<<spriteSheetState;
    UpinAir=true;
    AirState=1;
    qreal curPosY= y();
    jumpSound->stop();
    jumpSound->play();

    yScrollAnimationUp->setStartValue(yScrollPos->value());
    int  x=yScrollPos->value() - distance/2;
    yScrollAnimationUp->setEndValue(x);
    yScrollAnimationUp->setEasingCurve(QEasingCurve::Linear);
    yScrollAnimationUp->setDuration(distance);

    yAnimationUp->setStartValue(curPosY);
    yAnimationUp->setEndValue(curPosY - distance);
    yAnimationUp->setEasingCurve(QEasingCurve::OutQuad);
    yAnimationUp->setDuration(distance);

    playeryAxeScroll->start();
    //yAnimationUp->start();
    }
}
//-------------------------------------------------------------------------------------
void Player::Down()
{

    connect(playeryAxeScroll,&QPropertyAnimation::finished,[=](){
        if (y()< groundPosition)
        {
            AirState=2;

            spriteSheetState=((spriteSheetState/100)*100)+90+(spriteSheetState%10);  //*9*

            fall(groundPosition-y(),y(),groundPosition);

        }
    });
}
void Player::fall(int distance, int startValue, int groundPosition)
{

    AirState=2;
    frameTimer=35;
    yScrollAnimationDown->setStartValue(yScrollPos->value());
    int x=yScrollPos->value() + abs(distance)/2+100;
    yScrollAnimationDown->setEndValue(x);
    yScrollAnimationDown->setEasingCurve(QEasingCurve::Linear);
    yScrollAnimationDown->setDuration(abs(distance));


    yAnimationDown->setStartValue(startValue);
    yAnimationDown->setEndValue(groundPosition);
    yAnimationDown->setEasingCurve(QEasingCurve::OutQuad);
    yAnimationDown->setDuration(abs((distance*3)/2));
    playeryAxeScrollDown->start();
    //yAnimationDown->start();
    connect(playeryAxeScrollDown,&QPropertyAnimation::finished,[=](){
        frameTimer=80;
    });
}
//******************************   --Collision Detection --  ******************************************

bool Player::collideX()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        InanimateObject * inanimateObject =dynamic_cast<InanimateObject*>(item);
        Coin * coin =dynamic_cast<Coin*>(item);
        Castle * caslte =dynamic_cast<Castle*>(item);
        EndStage * endStage =dynamic_cast<EndStage*>(item);
        Fireflower * flower =dynamic_cast<Fireflower*>(item);

        if ((inanimateObject) && (!caslte))
        {
            qreal t;
            t=this->y();
            if (item->y()<t+playerHeight/2)
                if (((direction==0) && (item->x()>=this->x())) || ((direction==1) && (item->x()<=this->x())) )
                    return true;
        }
        else
         if (coin)
         {
             coin->taken();
         }
         else
          if (endStage)
          {
              stopWalking();
              endStage->NextMap();
          }
          else
           if (flower)
           {
               powerup(4);
               flower->taken();

           }

    }
    return false;
}
//-------------------------------------------------------------------------------------
QString Player::collideY()
{
  if (colided)
  {
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        Lake *lake=dynamic_cast<Lake*>(item);
        Koopa *koopa=dynamic_cast<Koopa*>(item);
        if (platform)
        {
            qreal t;
            t=this->y();
            if ((item->y()<t))
            {
               // qDebug()<<"Head collide";
                if (platform->getPlatformType()==3)
                    platform->destroyPlatform();
                else if (platform->getPlatformType()==4)
                    platform->Touched();
                if (platform->getPlatformType()!=-1)
                    return "head";
            }
            else
                if (item->y()>t)
                {
                    //qDebug()<<"foots";
                    playeryAxeScrollDown->stop();
                   return "foots";
                }
        }
        else
         if ((lake) &&(helth>0) &&(lake->y()<y()-280))
         {
             die();
         }
        else if (koopa)
         {
             setY(y()-10);
             AirState=0;
             Up(200);
             Down();
             if(x()<koopa->x())
                 koopa->groundState=1;
             else koopa->groundState=2;
                 koopa->hit();
                 return "koopa";

         }
    }
  }
    return "notcolliding";
}

//******************************    --Positioning--      *********************************

qreal Player::y() const
{
    return m_y;
}
//-------------------------------------------------------------------------------------
qreal Player::x() const
{
    return m_x;
}
//-------------------------------------------------------------------------------------
void Player::setY(qreal y)
{
    m_y = y;

    setPos(x(),m_y);


    if (collideY()!="notcolliding") // colliding
    {

        if ((collideY()=="foots") && (marioSize!=-1) && (AirState==2))
        {

            playeryAxeScrollDown->stop();
            m_y=y-10;
            if (AirState!=0)
            {
                AirState=0;
                if (groundState==0)
                  spriteSheetState=((spriteSheetState/100)*100)+10+(spriteSheetState%10); // *1*
                qDebug()<<"spriteSheetState after fall :: "<<spriteSheetState;

            }
            frameTimer=80;

        }
        else
            if ((collideY()=="head") && (AirState==1))  // head collide
            {
                if (AirState!=0)
                    AirState=0;
            //    qDebug()<<"Head ****";
                playeryAxeScroll->stop();
                setPos(QPoint(0,0)+QPoint(x(),y+20));
                fall(groundPosition-y+20,y+20,groundPosition);

            }


    }


    if(y>450)
            {

                die();

            }

}
//-------------------------------------------------------------------------------------
void Player::setX(qreal x)
{
    m_x = x;
    if (collideX())
    {
        if (direction==0)
            m_x = x-10;
        else
            m_x = x+10;
        stopWalking();
    }
    else
        if (collideY()=="notcolliding")
        {
            if (AirState==0)
                fall(groundPosition-y(),y(),groundPosition);
        }
    if ((xScrollPos->value()>m_x-950) )
    xScrollPos->setValue(m_x-950);



    setPos(QPoint(0,0)+QPoint(m_x,y()));
}

//******************************    --Mario Size--      *********************************

void Player::setMarioSize(int size)  //0:small   1:big
{
    marioSize=size;
    currentFrame=0;
    if (size==0)
    {
        playerHeight=160;
        speed=1;
        frameLength=192;
        setY(y()+64);
    }
    else
    {
        speed=1.5;
        playerHeight=210;
        frameLength=256;
        setY(y()-64);

    }
}
//-------------------------------------------------------------------------------------
void Player::powerup(int power)
{
transformSize();

helth=power;
spriteSheetState=(power*100)+(spriteSheetState%100);
powerupSound->stop();
powerupSound->play();
}

void Player::transformSize()
{
    timerMarioSize->start(60);

}

void Player::sizeCycle()
{

    if (marioSize==0)
    {
    setMarioSize(1);
    }
  else {
      setMarioSize(0);
    }
    if (tranformCount==0)
    {
        timerMarioSize->stop();
        tranformCount=10;
        if(helth==0)
            setMarioSize(0);
        else setMarioSize(1);
    }
    tranformCount--;
}



void Player::fastState()
{
    if (helth>0)
   {
   helth=4;
   speed=2;
   backgroundMusic->pause();
   backgroundMusic->stop();
   backgroundMusic->setMedia(QUrl("qrc:/sound/sound/Bonus Level.mp3"));

   backgroundMusic->play();
   fastTimer->start(12000);
   connect(fastTimer,&QTimer::timeout, this,[=](){
       speed=1.5;
       backgroundMusic->setMedia(QUrl("qrc:/sound/sound/overworld.ogg"));
       backgroundMusic->stop();
       backgroundMusic->play();
       helth=2;
       fastTimer->stop();
   });

    }
}

void Player::shootFire()
{
if (spriteSheetState/100==4)
{
spriteSheetState=((spriteSheetState/100)*100)+40+(spriteSheetState%10);
if (!shootingFire)
    currentFrame=0;
frameTimer=40;
  {
    spriteColumn=2048*frameLength/256;
    shootingFire=true;

    connect(shootTimer,&QTimer::timeout, this,[=]{
        fireball= new Fireball(x()+50,y()+100,direction);
        this->scene()->addItem(fireball);
        fireBallSound->stop();
        fireBallSound->play();
        stopWalking();
        spriteSheetState=((spriteSheetState/100)*100)+10+(spriteSheetState%10);
        shootingFire=false;
        shootTimer->stop();
        frameTimer=80;
    });
    shootTimer->start(300);
  }
}
}
//-------------------------------------------------------------------------------------
void Player::nextFrameBigMario()
{


    int x=spriteSheetState%100;
    switch (x) {
    case 11:
    case 21:
    case 41:
    {
        if(currentFrame>=spriteColumn-frameLength)
             currentFrame=0;
        else currentFrame += frameLength;
        break;
    }
    case 12:
    case 22:
    case 42:
    {
        if (currentFrame<frameLength)
            currentFrame=spriteColumn-frameLength;
        else currentFrame -= frameLength;
        break;
    }
    // Jump Up
    case 31:
    case 92:
    {
        if(currentFrame<spriteColumn-frameLength)
             currentFrame += frameLength;
        break;
    }
    case 32:
    case 91:
    {
        if (currentFrame>=frameLength)
            currentFrame -= frameLength;
        break;
    }

    }

    timerBigMario->stop();
    timerBigMario->start(frameTimer);

    update(0,0,frameLength,frameLength);

}
//-------------------------------------------------------------------------------------
void Player::nextFrameSmallMario()
{

}

//*******************************************************************************************

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
  //  qDebug()<<"spriteSheetState paint :: "<<spriteSheetState;

    if(shootingFire){
        switch (spriteSheetState) {
        //Fire mario Throw FireBall
        case 441:{ painter->drawPixmap(0,0, *spriteImageFireMarioThrowBallRight, currentFrame, 0, frameLength,frameLength); break;}
        case 442:{ painter->drawPixmap(0,0, *spriteImageFireMarioThrowBallLeft, currentFrame, 0, frameLength,frameLength); break;}
        }
    }
    else
    {
    switch (spriteSheetState) {
    //small mario
    case 111:{ painter->drawPixmap(0,0, *spriteImageSmallMarioBreathRight, currentFrame, 0, frameLength,frameLength); break;}
    case 112:{ painter->drawPixmap(0,0, *spriteImageSmallMarioBreathLeft, currentFrame, 0, frameLength,frameLength); break;}
    case 121:{ painter->drawPixmap(0,0, *spriteImageSmallMarioWalkRight, currentFrame, 0, frameLength,frameLength); break;}
    case 122:{ painter->drawPixmap(0,0, *spriteImageSmallMarioWalkLeft, currentFrame, 0, frameLength,frameLength); break;}
    case 131:
    case 191:{ painter->drawPixmap(0,0, *spriteImageSmallMarioJumpRight, currentFrame, 0, frameLength,frameLength); break;}
    case 132:
    case 192:{ painter->drawPixmap(0,0, *spriteImageSmallMarioJumpLeft, currentFrame, 0, frameLength,frameLength); break;}
    //Big mario + Fast Mario
    case 311:
    case 211:{if ((speed==2) && ((currentFrame/256)%2==0))
               painter->drawPixmap(0,0, *spriteImageBigMarioBreathRightFast, currentFrame, 0, frameLength,frameLength);
              else
              painter->drawPixmap(0,0, *spriteImageBigMarioBreathRight, currentFrame, 0, frameLength,frameLength); break;}
    case 312:
    case 212:{if ((speed==2) && ((currentFrame/256)%2==0))
                painter->drawPixmap(0,0, *spriteImageBigMarioBreathLeftFast, currentFrame, 0, frameLength,frameLength);
               else
               painter->drawPixmap(0,0, *spriteImageBigMarioBreathLeft, currentFrame, 0, frameLength,frameLength); break;}
    case 321:
    case 221:{if ((speed==2) && ((currentFrame/256)%2==0))
                    painter->drawPixmap(0,0, *spriteImageBigMarioWalkRightFast, currentFrame, 0, frameLength,frameLength);
               else
               painter->drawPixmap(0,0, *spriteImageBigMarioWalkRight, currentFrame, 0, frameLength,frameLength); break;}
    case 322:
    case 222:{ if ((speed==2) && ((currentFrame/256)%2==0))
                  painter->drawPixmap(0,0, *spriteImageBigMarioWalkLeftFast, currentFrame, 0, frameLength,frameLength);
                else
                painter->drawPixmap(0,0, *spriteImageBigMarioWalkLeft, currentFrame, 0, frameLength,frameLength); break;}
    case 231:
    case 291:{  painter->drawPixmap(0,0, *spriteImageBigMarioJumpRight, currentFrame, 0, frameLength,frameLength); break;}
    case 232:
    case 292:{  painter->drawPixmap(0,0, *spriteImageBigMarioJumpLeft, currentFrame, 0, frameLength,frameLength); break;}
    // Fire Mario
    case 411:{ painter->drawPixmap(0,0, *spriteImageFireMarioBreathRight, currentFrame, 0, frameLength,frameLength); break;}
    case 412:{ painter->drawPixmap(0,0, *spriteImageFireMarioBreathLeft, currentFrame, 0, frameLength,frameLength); break;}
    case 421:{ painter->drawPixmap(0,0, *spriteImageFireMarioWalkRight, currentFrame, 0, frameLength,frameLength); break;}
    case 422:{ painter->drawPixmap(0,0, *spriteImageFireMarioWalkLeft, currentFrame, 0, frameLength,frameLength); break;}
    case 431:
    case 491:{ painter->drawPixmap(0,0, *spriteImageFireMarioJumpRight, currentFrame, 0, frameLength,frameLength); break;}
    case 432:
    case 492:{ painter->drawPixmap(0,0, *spriteImageFireMarioJumpLeft, currentFrame, 0, frameLength,frameLength); break;}
    }

}
}
QRectF Player::boundingRect() const
{
    return QRectF(0,0,frameLength,frameLength);
}
QPainterPath Player::shape() const
{
    QPainterPath path;
    if (marioSize==1)
    {
        path.addRect(30, 0, 100, 210);
    } else     {
        path.addRect(21, 0, 100, 160);
    }
    return path;
}






