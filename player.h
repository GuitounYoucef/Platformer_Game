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

#include"bullet.h"
#include"backgroundimage.h"
#include"walkers.h"

class QScrollBar;


class Player :   public Walkers
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Player(QGraphicsView *graphicsView,QGraphicsScene *scenePlayer,BackgroundImage *background);
    void addBackground();
    void Jump();
    void addBullet();
    void walk(int direct,BackgroundImage *background);
    void fall(int distance, int startValue, int groundPosition);
    void stopWalking();
    void powerup();
    void die();

    void Up(int distance);
    void Down();
    QString collideY();
    bool collideX();

    bool UpinAir=false;

    bool inGround=true;
    qreal y() const;
    //void fall(int distance,int startValue);
    void setMarioSize(int size);  //0:small    1:big

   // qreal x() const;

    qreal x() const;

signals:


public slots:
    void setY(qreal y);




    //void setX(qreal x);

    void setX(qreal x);





private:
     QScrollBar *scroll;
     QScrollBar *xScrollPos;
     QScrollBar *yScrollPos;
     QParallelAnimationGroup *playerScroll; // group animation player+scrollBar
     QParallelAnimationGroup *playeryAxeScroll;
     QParallelAnimationGroup *playeryAxeScrollDown;
     int viewWidth;

    QMediaPlayer *backgroundMusic;
    QMediaPlayer *jumpSound;
    QMediaPlayer *powerupSound;
    QMediaPlayer *DieSound;
//*********************************************

    int playerWidth=75;
    int playerHeight=185;
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
    Bullet *bullet;
    qreal yPos;
    bool collideStat=true;

    QPainter *painter;
    int marioSize=1; // 0:small , 1:Big, -1:die

    QPixmap *spriteImageBigMario;   // In this QPixmap object will be placed sprite
    QPixmap *spriteImageSmallMario;




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
