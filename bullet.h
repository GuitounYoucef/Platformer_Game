#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Bullet :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Bullet(int x,int direction);
    void move();

signals:

public slots:
  //  void move();

private:
       QTimer *timer;
       QPropertyAnimation * xAnimation;


};

#endif // BULLET_H
