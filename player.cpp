#include "player.h"
#include<QGraphicsView>
#include"platform.h"
#include"inanimateobject.h"
#include"coin.h"
#include<QDebug>
#include <QScrollBar>
#include<QParallelAnimationGroup>


Player::Player(QGraphicsView *graphicsView,QGraphicsScene *scenePlayer,BackgroundImage *background)
{
    currentFrame = 0;
    spriteImageBigMario = new QPixmap(QPixmap(":/images/BigMarioSprite.png"));
    spriteImageSmallMario = new QPixmap(QPixmap(":/images/marioWalkRight.png"));
    backgroundAnimation = new QPropertyAnimation(background,"x");
    imageXpos=background->x();

    line=200;
    timerSmallMario = new QTimer();
    timerBigMario = new QTimer();
    connect(timerSmallMario, &QTimer::timeout, this, &Player::nextFrameSmallMario);
    connect(timerBigMario, &QTimer::timeout, this, &Player::nextFrameBigMario);
    timerBigMario->start(frameTimer);

    groundPosition=500;
    yPos=groundPosition;

    graphicsView->setScene(scenePlayer);
    viewWidth= 1900;

    xScrollPos=graphicsView->horizontalScrollBar();

    xScrollPos->setValue(-950);
    ScrollAnimation = new QPropertyAnimation(xScrollPos,"value");
    playerScroll = new QParallelAnimationGroup;
    playerScroll->addAnimation(xAnimation);
    playerScroll->addAnimation(ScrollAnimation);
    playerScroll->addAnimation(backgroundAnimation);

    jumpSound=new QMediaPlayer();
    jumpSound->setMedia(QUrl("qrc:/sound/sound/Jump.wav"));

    powerupSound=new QMediaPlayer();
    powerupSound->setMedia(QUrl("qrc:/sound/sound/Powerup.wav"));

}


//******************************   --Movement--  ******************************************
void Player::Jump()
{
    UpinAir=false;
    frameTimer=playerHeight/24;
    currentFrame=0;
    Up();
    Down();
}
//-------------------------------------------------------------------------------------
void Player::addBullet()
{
    bullet = new Bullet(x(),direction);
    bullet->setPos(x()+40,y()+30);
    scene()->addItem(bullet);
    bullet->move();
}
//-------------------------------------------------------------------------------------
void Player::walk(int dirc,BackgroundImage *background,bool withCamera)
{
    frameTimer=35;
    direction=dirc;
    int step;
    int duration;
    xAnimation->stop();
    ScrollAnimation->stop();
    backgroundAnimation->stop();
    if (AirState==0)
    {
        step=1200;
        duration=2100;
    }
    else
    {
        step=600;
        duration=2100;
    }
    xAnimation->setStartValue(x());
    ScrollAnimation->setStartValue(xScrollPos->value());
    backgroundAnimation->setStartValue(background->x());
    if (direction==0)                   // 0:walk Raight ; 1:walk Left
    {
        groundState=1;
        xAnimation->setEndValue(x()+step);
        ScrollAnimation->setEndValue(xScrollPos->value()+step);
        if(background->pixmap().width()+background->x()<scene()->width()-600)
            backgroundAnimation->setEndValue(background->x()+step-200);
        else
            backgroundAnimation->setEndValue(background->x());

    }
    else
    {
        groundState=2;
        xAnimation->setEndValue(x()-step);
        ScrollAnimation->setEndValue(xScrollPos->value()-step);
        if(background->x()>-950)
            backgroundAnimation->setEndValue(background->x()-step+200);
        else
            backgroundAnimation->setEndValue(background->x());

    }
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    ScrollAnimation->setEasingCurve(QEasingCurve::Linear);
    backgroundAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(duration);
    ScrollAnimation->setDuration(duration);
    backgroundAnimation->setDuration(duration);
    if  ((withCamera) &&( ( x()-950 >(xScrollPos->value()+viewWidth/6) && (direction==0)  )
                          || (( (x()-950 <(xScrollPos->value()-viewWidth/6) ) && (direction==1)))))
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
 playerScroll->stop();
 xAnimation->stop();
 groundState=0;
 frameTimer=80;
}

void Player::powerup()
{
if (marioSize==0){
    setMarioSize(1);
}
powerupSound->stop();
powerupSound->play();

}
//-------------------------------------------------------------------------------------
void Player::Up()
{
    if (AirState==0)
    {
    UpinAir=true;
    AirState=1;
    qreal curPosY= y();
    jumpSound->stop();
    jumpSound->play();
    yAnimationUp->setStartValue(curPosY);
    yAnimationUp->setEndValue(curPosY - playerHeight*3);
    yAnimationUp->setEasingCurve(QEasingCurve::OutQuint);
    yAnimationUp->setDuration(playerHeight*4);
    yAnimationUp->start();
    }
}
//-------------------------------------------------------------------------------------
void Player::Down()
{
    connect(yAnimationUp,&QPropertyAnimation::finished,[=](){
        if (y()< groundPosition)
        {

            UpinAir=false;
            AirState=2;
            fall(groundPosition-y(),y(),groundPosition);
        }
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
        if ((inanimateObject))
        {
            qreal t;
            t=this->y();
            if (item->y()<t)
                if (((direction==0) && (item->x()>=this->x())) || ((direction==1) && (item->x()<=this->x())) )
                    return true;
        }
        else
         if (coin)
         {
             coin->taken();
         }

    }
    return false;
}
//-------------------------------------------------------------------------------------
QString Player::collideY()
{
    QList<QGraphicsItem*> collidingItems=this->collidingItems();
    foreach(QGraphicsItem * item,collidingItems)
    {
        Platform * platform =dynamic_cast<Platform*>(item);
        if (platform)
        {
            qreal t;
            t=this->y();
            if ((item->y()<t+playerHeight*4/5))
            {
                qDebug()<<"Head collide";
                if (platform->getPlatformType()==3)
                    platform->destroyPlatform();
                else if (platform->getPlatformType()==4)
                    platform->Touched();
                if (platform->getPlatformType()!=-1)
                    return "head";
            }
            else
                if ((item->y()>t+playerHeight*4/5))
                {
                    qDebug()<<"foots";
                    return "foots";
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
    if (collideY()!="notcolliding") // colliding
    {
        if ((collideY()=="foots") && (AirState==2))
        {
            yAnimationDown->stop();
            m_y=y-10;
            if (AirState!=0)
                AirState=0;
            frameTimer=80;
        }
        else
            if ((collideY()=="head") && (AirState==1))  // head collide
            {
                if (AirState!=0)
                    AirState=0;
                qDebug()<<"Head ****";
                yAnimationUp->stop();
                setPos(QPoint(0,0)+QPoint(x(),y+20));
                fall(groundPosition-y+20,y+20,groundPosition);

            }
    }
    setPos(QPoint(0,0)+QPoint(x(),m_y));
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
    setPos(QPoint(0,0)+QPoint(m_x,y()));
}

//******************************    --Mario Size--      *********************************

void Player::setMarioSize(int size)  //0:small   1:big
{
    marioSize=size;
    currentFrame=0;
    if (size==0)
    {
        playerWidth=38;
        playerHeight=93;
        shape();
        timerBigMario->stop();
        connect(timerSmallMario, &QTimer::timeout, this, &Player::nextFrameSmallMario);
        timerSmallMario->start(frameTimer);
        setY(y()+playerHeight);
    }
    else
    {
        playerWidth=75;
        playerHeight=185;
        shape();
        timerSmallMario->stop();
        connect(timerBigMario, &QTimer::timeout, this, &Player::nextFrameBigMario);
        timerBigMario->start(frameTimer);
        setY(y()-playerHeight/2);
    }
}
//-------------------------------------------------------------------------------------
void Player::nextFrameBigMario()
{
    spriteColumn=3800;
    if (AirState!=0)  // jumping animation
    {
        spriteColumn=2834;
        if((frameTimer<playerHeight*7/4) &&(AirState==1) )
            frameTimer=frameTimer*2;
        else if (frameTimer>160)
            frameTimer=frameTimer/2;
    }
    else
    {
        if (groundState==1)
        {
            line=1536;
        }
        else if (groundState==2)
        {
            line=1792;
        }
        else
        {
            if (direction==0)
                line=0;
            else line=256;
        }
    }
    if (frameDirection==1)
        currentFrame += 256;
    else currentFrame -= 256;
    if ((currentFrame >= spriteColumn ) ){
        if (spriteColumn==3800)
        {
            currentFrame =0;
            frameDirection=+1;
        }
        else
        {
            currentFrame -= 256;

            frameDirection=-1;
        }
    }
    if (currentFrame <0 )
    {
        currentFrame =0;
        frameDirection=1;
    }
    timerBigMario->stop();
    timerBigMario->start(frameTimer);

    update(0,0,256,256);
}
//-------------------------------------------------------------------------------------
void Player::nextFrameSmallMario()
{
    if (AirState!=0)  // jumping animation
    {
        if (direction==0) // left
            line=2535/2;
        else if (direction==1) // right
            line=2796/2;
    }
    else
        if (groundState==1)
        {

            line=1536/2;
        }
        else if (groundState==2)
        {
            line=1792/2;
        }
        else if (direction==0)
            line=0;
        else line=128;
    if (frameDirection==1)
        currentFrame += 128;
    else currentFrame = currentFrame-256/2;
    if ((currentFrame >= 4000/2 ) ){
        currentFrame -= 128;
        frameDirection=-1;
    }
    if (currentFrame <0 )
    {
        currentFrame =0;
        frameDirection=1;
    }
    timerSmallMario->stop();
    timerSmallMario->start(frameTimer);
    update(0,0,128,128);
}

//*******************************************************************************************

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (marioSize==0)
    painter->drawPixmap(0,0, *spriteImageSmallMario, currentFrame, line, 90,100);
    else
     painter->drawPixmap(0,0, *spriteImageBigMario, currentFrame, line, 180,200);
}
QRectF Player::boundingRect() const
{
    return QRectF(0,0,180,250);
}
QPainterPath Player::shape() const
{
    QPainterPath path;
    if (marioSize==0)
        path.addRect(35/2, 0, playerWidth, playerHeight);
    else
        path.addRect(35, 0, playerWidth, playerHeight);
    return path;
}






