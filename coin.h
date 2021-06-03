#ifndef COIN_H
#define COIN_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include<QMediaPlayer>

class Coin : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Coin(int x,int y);
    void taken();

signals:


private:

    QPixmap *spriteImageCoin;
    int currentFrame, line;
    void nextFrame();
    QTimer *timer;
    QMediaPlayer *coinSound;

    QPainterPath shape() const Q_DECL_OVERRIDE;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   QRectF boundingRect() const;

};

#endif // COIN_H
