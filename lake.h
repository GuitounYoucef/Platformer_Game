#ifndef LAKE_H
#define LAKE_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Lake : public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Lake(int xpos,int ypos,int width);
    int Lakewidth;
    int i=0;

signals:

private:

};

#endif // LAKE_H
