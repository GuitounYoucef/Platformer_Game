#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include"walkers.h"

class Mushroom :   public Walkers
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    qreal m_x;

    qreal m_y;

public:
    explicit Mushroom();

    qreal x() const;
    qreal y() const;

    void start();
    void walk(int direc);

public slots:
    void setX(qreal x);
    void setY(qreal y);
    QString collideY();
    QString collideX();

signals:
private:
    QTimer *timer;




};

#endif // MUSHROOM_H
