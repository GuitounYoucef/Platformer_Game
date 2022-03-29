#ifndef KOOPA_H
#define KOOPA_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include<QDebug>
#include<QMediaPlayer>

#include"walkers.h"
#include "platform.h"
#include "player.h"



class Koopa:public Walkers,public QGraphicsPixmapItem
{

    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    qreal m_x;

    qreal m_y;

public:
    explicit Koopa(int x,int y);
    virtual ~Koopa();
    void setKoopastate();
    void hit();

    QPixmap *SpriteImageWalkLeft;
    QPixmap *SpriteImageWalkRight;
    QPixmap *SpriteImageShell;


    int frametime=50;
    int frameNumber;
    int height, width;
    int spriteState=1; // 1:walking 0: only shell
    int koopaState=1;  // 1:koopa     2:shell stoped   3:shell move   4:shell hited

    qreal x() const;
    qreal y() const;
    QString collideY();
    QString collideX();


public slots:
    void setX(qreal x);
    void setY(qreal y);



private:
    void walk();
    void nextFrame();

    QTimer *timer;
    QTimer *walktimer;
    QTimer *dieTimer;
    QTimer *changeStateTimer;
    int Heightsize=50;
    int speed=1;
    //******************************

    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;


};

#endif // KOOPA_H
