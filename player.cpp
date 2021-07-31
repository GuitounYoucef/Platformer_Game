#include "player.h"
#include<QGraphicsView>
#include"platform.h"
#include"inanimateobject.h"
#include"coin.h"
#include<QDebug>
#include <QScrollBar>
#include<QParallelAnimationGroup>
#include"castle.h"


Player::Player(QGraphicsView *graphicsView,QGraphicsScene *scenePlayer,BackgroundImage *background)
{
    currentFrame = 0;
    spriteImageBigMario = new QPixmap(QPixmap(":/images/BigMarioSprite.png"));
    spriteImageSmallMario = new QPixmap(QPixmap(":/images/mario-sprite-png.png"));
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
    yScrollPos=graphicsView->verticalScrollBar();

    xScrollPos->setValue(-950);
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
    backgroundMusic->setVolume(50);
   // backgroundMusic->play();

}


//******************************   --Movement--  ******************************************
void Player::Jump()
{
    UpinAir=false;
    frameTimer=playerHeight/24;
    currentFrame=0;
    Up(playerHeight*3);
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
void Player::walk(int dirc,BackgroundImage *background)
{
    frameTimer=35;
    direction=dirc;
    int step;
    int duration;
    xAnimation->stop();
    xScrollAnimation->stop();
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
    xScrollAnimation->setStartValue(xScrollPos->value());
    backgroundAnimation->setStartValue(background->x());
    if (direction==0)                   // 0:walk Right ; 1:walk Left
    {
        groundState=1;
        xAnimation->setEndValue(x()+step);
        xScrollAnimation->setEndValue(xScrollPos->value()+step);
        if(background->pixmap().width()+background->x()<scene()->width()-600)
            backgroundAnimation->setEndValue(background->x()+step-200);
        else
            backgroundAnimation->setEndValue(background->x());
    }
    else
    {
        groundState=2;
        xAnimation->setEndValue(x()-step);
        xScrollAnimation->setEndValue(xScrollPos->value()-step);
        if(background->x()>-950)
            backgroundAnimation->setEndValue(background->x()-step+200);
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
                          || (( (x()-950 <(xScrollPos->value()-viewWidth/12) ) && (direction==1)))))
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
//-------------------------------------------------------------------------------------
void Player::powerup()
{
if (marioSize==0){
    setMarioSize(1);
}
powerupSound->stop();
powerupSound->play();
}
//-------------------------------------------------------------------------------------
void Player::die()
{
marioSize=-1;
helth=0;
Up(playerHeight);
Down();
backgroundMusic->stop();
DieSound->play();
}
//-------------------------------------------------------------------------------------
void Player::Up(int distance)
{
    if (AirState==0)
    {
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
    yAnimationUp->setEasingCurve(QEasingCurve::OutQuint);
    yAnimationUp->setDuration(distance/3*4);

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
            fall(groundPosition-y(),y(),groundPosition);

        }
    });
}
void Player::fall(int distance, int startValue, int groundPosition)
{
    AirState=2;
    yScrollAnimationDown->setStartValue(yScrollPos->value());
    int  x=yScrollPos->value() + abs(distance)/2;
    yScrollAnimationDown->setEndValue(x);
    yScrollAnimationDown->setEasingCurve(QEasingCurve::Linear);
    yScrollAnimationDown->setDuration(abs(distance));


    yAnimationDown->setStartValue(startValue);
    yAnimationDown->setEndValue(groundPosition);
    yAnimationDown->setEasingCurve(QEasingCurve::Linear);
    yAnimationDown->setDuration(abs(distance));
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
            if ((item->y()<t))
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
                if ((item->y()>t))
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
    setPos(x(),m_y);
    if (collideY()!="notcolliding") // colliding
    {
        if ((collideY()=="foots") && (marioSize!=-1) && (AirState==2))
        {
            playeryAxeScrollDown->stop();
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
                playeryAxeScroll->stop();
                setPos(QPoint(0,0)+QPoint(x(),y+20));
                fall(groundPosition-y+20,y+20,groundPosition);

            }
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
        if (direction==0) // left
            line=2535;
        else if (direction==1) // right
            line=2796;

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
    spriteColumn=1900;
    if (AirState!=0)  // jumping animation
    {
        spriteColumn=2834/2;
        if (direction==0) // left
            line=2535/2;
        else if (direction==1) // right
            line=2796/2;

        if((frameTimer<playerHeight*7/4) &&(AirState==1) )
            frameTimer=frameTimer*2;
        else if (frameTimer>160)
            frameTimer=frameTimer/2;
    }
    else
    {
        if (groundState==1)
        {
            line=1536/2;
        }
        else if (groundState==2)
        {
            line=1792/2;
        }
        else
        {
            if (direction==0)
                line=0;
            else line=256/2;
        }
    }
    if (frameDirection==1)
        currentFrame += 256/2;
    else currentFrame -= 256/2;
    if ((currentFrame >= spriteColumn ) ){
        if (spriteColumn==1900)
        {
            currentFrame =0;
            frameDirection=+1;
        }
        else
        {
            currentFrame -= 256/2;

            frameDirection=-1;
        }
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






