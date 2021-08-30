#ifndef WATER_H
#define WATER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include<QTimer>
#include <QPainter>

class Water : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Water(int xpos,int ypos);






private:

    QPixmap *spriteImageWater;
    int currentFrame, line;
    void nextFrame();
    QTimer *timer;


    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // WATER_H
