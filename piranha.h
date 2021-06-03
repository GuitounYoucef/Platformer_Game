#ifndef PIRANHA_H
#define PIRANHA_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Piranha : public QObject,public QGraphicsPixmapItem

{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Piranha();

    qreal y() const;

public slots:
    void setY(qreal y);

signals:
private:

    QPixmap *spriteImageCoin;
    int currentFrame, line;
    void nextFrame();
    QTimer *timer;
    QTimer *timerYanimation;
    QGraphicsPixmapItem *pipe;
    QPropertyAnimation *yAnimationUp;
    QPropertyAnimation *yAnimationDown;

    QPainterPath shape() const Q_DECL_OVERRIDE;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   QRectF boundingRect() const;


   qreal m_y;
};

#endif // PIRANHA_H
