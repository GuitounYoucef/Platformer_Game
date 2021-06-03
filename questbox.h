#ifndef QUESTBOX_H
#define QUESTBOX_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Questbox : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Questbox();

signals:
private:

    QPixmap *spriteImageCoin;
    int currentFrame, line;
    void nextFrame();
    QTimer *timer;

    QPainterPath shape() const Q_DECL_OVERRIDE;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   QRectF boundingRect() const;

};

#endif // QUESTBOX_H
