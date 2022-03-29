#ifndef FIREBALL_H
#define FIREBALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QParallelAnimationGroup>
#include<QSequentialAnimationGroup>
#include"platform.h"
#include "enemy.h"




class Fireball : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Fireball(qreal x,qreal y,int direction);
    void nextFrame();
    bool collideY();
    bool collideX();
    void startMoveAnimation();

    qreal y() const;

    qreal x() const;

public slots:
    void setY(qreal y);

    void setX(qreal x);

signals:

private:
    QPixmap *spriteImageFireRight;
    QPixmap *spriteImageFireLeft;
    QTimer *timer;
    QTimer *collideTimer;
    QTimer *framesTimer;
    QTimer *rotationTimer;


    QPropertyAnimation * xAnimation;
    QPropertyAnimation * upAnimation;
    QPropertyAnimation * fallAnimation;
    QSequentialAnimationGroup *UpFallSeqAnimation;

    QParallelAnimationGroup *moveAnimation;
    int currentFrame;
    int framedirection=1;
    qreal xdirec;
    qreal ydirec=50;
    int ypos;
    int rotation=0;
    int angle=2;
    qreal steps=5;

    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    qreal m_y;
    qreal m_x;
};

#endif // FIREBALL_H
