#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include<QParallelAnimationGroup>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include<QMediaPlayer>
#include<QThread>
#include<QGraphicsPixmapItem>

#include"bullet.h"
#include"backgroundimage.h"
#include"walkers.h"
#include "fireball.h"



class QScrollBar;


class Player :   public Walkers,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Player(QGraphicsView *graphicsView,QGraphicsScene *scenePlayer,BackgroundImage *background);
    ~Player();
    void addBackground();
    void Jump();
    void addBullet();
    void walk(int direct,BackgroundImage *background);
    void fall(int distance, int startValue, int groundPosition);
    void stopWalking();
    void powerup(int power);
    void fastState();
    void transformSize();
    void sizeCycle();
    void shootFire();


    void Up(int distance);
    void Down();
    QString collideY();
    bool collideX();

    bool UpinAir=false;
    int helth=1;
    BackgroundImage *backgroundimage;
    int playerWidth=180;
    int playerHeight=160;
    int frameLength=192;
    float speed=1;
    int marioSize=5; // 0:small , 1:Big, -1:die
    bool shootingFire=false;


    bool inGround=true;
    qreal y() const;
    //void fall(int distance,int startValue);
    void setMarioSize(int size);  //0:small    1:big

   // qreal x() const;
    void die();
    qreal x() const;
    //*********************************************
   QMediaPlayer *backgroundMusic;
   QMediaPlayer *DieSound;



signals:
    void RetCheckPoint();

public slots:
    void setY(qreal y);





    //void setX(qreal x);

    void setX(qreal x);





private:

     QScrollBar *scroll;
     QScrollBar *xScrollPos;
     QScrollBar *yScrollPos;
     QParallelAnimationGroup *playerScroll; // group animation player+scrollBar
     QParallelAnimationGroup *playeryAxeScroll; //jump
     QParallelAnimationGroup *playeryAxeScrollDown;  //fall
     int viewWidth;


    QMediaPlayer *jumpSound;
    QMediaPlayer *powerupSound;

    QMediaPlayer *fireBallSound;
    QTimer *dieTimer;
    QTimer *fastTimer;

    Fireball *fireball;

//*********************************************

    QPropertyAnimation * xScrollAnimation;
    QPropertyAnimation * yScrollAnimationUp;
    QPropertyAnimation * yScrollAnimationDown;
    QPropertyAnimation * backgroundAnimation;
    qreal imageXpos;


    qreal groundPosition;
    QPixmap * pixItem;
    QTimer *timerSmallMario;
    QTimer *timerBigMario;
    QTimer *timerMarioSize;
    QTimer *shootTimer;

    int tranformCount=10;
    Bullet *bullet;

    qreal yPos;
    bool collideStat=true;

    QPainter *painter;




    int spriteSheetState;  // 111 : SmallMario-Breath-Right
                               // 112 : SmallMario-Breath-Left
                               // 121 : SmallMario-Walk-Right
                               // 122 : SmallMario-Walk-Left
                               // 131 : SmallMario-Jump-Right
                               // 132 : SmallMario-Jump-Left
                               // 191 : SmallMario-JumpFall-Right
                               // 192 : SmallMario-JumpFall-Left

                                   // 211 : BigMario-Breath-Right
                                   // 212 : BigMario-Breath-Left
                                   // 221 : BigMario-Walk-Right
                                   // 222 : BigMario-Walk-Left
                                   // 231 : BigMario-Jump-Right
                                   // 232 : BigMario-Jump-Left

                                   // 311 : FastMario-Breath-Right
                                   // 312 : FastMario-Breath-Left
                                   // 321 : FastMario-Walk-Right
                                   // 322 : FastMario-Walk-Left
                                   // 331 : FastMario-Jump-Right
                                   // 332 : FastMario-Jump-Left

                                   // 411 : FireMario-Breath-Right
                                   // 412 : FireMario-Breath-Left
                                   // 421 : FireMario-Walk-Right
                                   // 422 : FireMario-Walk-Left
                                   // 431 : FireMario-Jump-Right
                                   // 432 : FireMario-Jump-Left
                                   // 441 : FireMario-ThrowFire-Right
                                   // 442 : FireMario-ThrowFire-Left


    QPixmap *spriteImageBigMario;   // In this QPixmap object will be placed sprite
    QPixmap *spriteImageSmallMario;

    QPixmap *spriteImageBigMarioWalkRight;
    QPixmap *spriteImageBigMarioWalkLeft;
    QPixmap *spriteImageBigMarioBreathRight;
    QPixmap *spriteImageBigMarioBreathLeft;

    QPixmap *spriteImageBigMarioJumpRight;
    QPixmap *spriteImageBigMarioJumpLeft;

    //Fire Mario
    QPixmap *spriteImageFireMarioWalkRight;
    QPixmap *spriteImageFireMarioWalkLeft;
    QPixmap *spriteImageFireMarioBreathRight;
    QPixmap *spriteImageFireMarioBreathLeft;

    QPixmap *spriteImageFireMarioJumpRight;
    QPixmap *spriteImageFireMarioJumpLeft;

    QPixmap *spriteImageFireMarioThrowBallRight;
    QPixmap *spriteImageFireMarioThrowBallLeft;
    //**********

    QPixmap *spriteImageBigMarioWalkRightFast;
    QPixmap *spriteImageBigMarioWalkLeftFast;
    QPixmap *spriteImageBigMarioBreathRightFast;
    QPixmap *spriteImageBigMarioBreathLeftFast;

    QPixmap *spriteImageSmallMarioWalkRight;
    QPixmap *spriteImageSmallMarioWalkLeft;
    QPixmap *spriteImageSmallMarioBreathRight;
    QPixmap *spriteImageSmallMarioBreathLeft;

    QPixmap *spriteImageSmallMarioJumpRight;
    QPixmap *spriteImageSmallMarioJumpLeft;





  //  void collideYanimation();
   void nextFrameBigMario();
   void nextFrameSmallMario();
   QPainterPath shape() const Q_DECL_OVERRIDE;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   QRectF boundingRect() const;





    qreal m_y;

    qreal m_x;



};

#endif // PLAYER_H
