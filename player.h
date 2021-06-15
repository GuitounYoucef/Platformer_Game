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
    void walk(int direct,BackgroundImage *background,bool withCamera);
    void stopWalking();
    void powerup();

    void Up();
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
     QScrollBar* xScrollPos;
     QParallelAnimationGroup * playerScroll; // group animation player+scrollBar
     int viewWidth;


    QMediaPlayer *jumpSound;
    QMediaPlayer *powerupSound;
//*********************************************

    int playerWidth=75;
    int playerHeight=185;
//*********************************************

    QPropertyAnimation * ScrollAnimation;  
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
    int marioSize=1; // 0:small , 1:Big

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
