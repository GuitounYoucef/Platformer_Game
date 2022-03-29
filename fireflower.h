#ifndef FIREFLOWER_H
#define FIREFLOWER_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>

#include <QPixmap>

class Fireflower : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)
    qreal m_x;

    qreal m_y;
public:
    explicit Fireflower();
    void start();
    void taken();

    qreal y() const;

    qreal x() const;

public slots:
    void setY(qreal y);

    void setX(qreal x);

signals:
private:
    QPixmap *spriteImageFireFlower;
    QPropertyAnimation * yAnimationUp;


};

#endif // FIREFLOWER_H
