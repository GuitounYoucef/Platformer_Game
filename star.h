#ifndef STAR_H
#define STAR_H
#include<QGraphicsPixmapItem>

#include"walkers.h"

class Star : public Walkers,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    qreal m_x;

    qreal m_y;
public:
    explicit Star();

    qreal x() const;
    qreal y() const;

    void start();
    void walk(int direc);
    void Up(int distance);

public slots:
    void setX(qreal x);
    void setY(qreal y);
    QString collideY();
    QString collideX();

signals:

private:
    QTimer *timer;

};

#endif // STAR_H
