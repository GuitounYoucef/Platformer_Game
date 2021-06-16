#ifndef GOOMBA_H
#define GOOMBA_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include"walkers.h"

class Goomba :public Walkers
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit Goomba();
    void walk(int direc);

    qreal x() const;
    qreal y() const;

public slots:
    void setX(qreal x);
    void setY(qreal y);
    QString collideY();
    signals:

private:
    QPixmap *spriteImageGoomba;
    int currentFrame, line;
    void nextFrame();
    QTimer *timer;



    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    qreal m_x;

    qreal m_y;

};

#endif // GOOMBA_H
