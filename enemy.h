#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include<QDebug>
#include<QMediaPlayer>

#include"walkers.h"
#include "platform.h"


class Enemy :public Walkers
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit Enemy();
    void walk();
    qreal x() const;
    qreal y() const;
    void start(int frametime);
    void die();
    QPixmap *SpriteImageWalkLeft;
    QPixmap *SpriteImageWalkRight;

    QPixmap *SpriteImageWalkLeftDie;
    QPixmap *SpriteImageWalkRightDie;
    int xpos,ypos;
    int frameNumber;
    int height, width;
    QMediaPlayer *DieSound;
    int helth=1;


public slots:
    void setX(qreal x);
    void setY(qreal y);
    QString collideY();
    QString collideX();
    signals:

private:

    void nextFrame();
    QTimer *timer;
    QTimer *walktimer;
    QTimer *dieTimer;
    int Heightsize=50;
    //******************************

    //******************************

    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    qreal m_x;

    qreal m_y;
};

#endif // ENEMY_H
