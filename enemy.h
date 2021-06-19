#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include<QDebug>
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
    QPixmap *SpriteImageWalkLeft;
    QPixmap *SpriteImageWalkRight;
    int xpos,ypos;
    int frameNumber;
    int height, width;


public slots:
    void setX(qreal x);
    void setY(qreal y);
    QString collideY();
    signals:

private:
    QPixmap *spriteImageWalkLeft;
    QPixmap *spriteImageWalkRigh;
    void nextFrame();
    QTimer *timer;
    QTimer *walktimer;
    //******************************

    //******************************

    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    qreal m_x;

    qreal m_y;
};

#endif // ENEMY_H
