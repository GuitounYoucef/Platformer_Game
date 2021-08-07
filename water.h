#ifndef WATER_H
#define WATER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include<QTimer>

class Water : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Water(int xpos,int ypos);


    qreal x() const
    {
        return m_x;
    }

public slots:

    void setX(qreal x);
private:

    QPixmap *waterImage;
    QTimer *timer;
    QPropertyAnimation *xAnimation;
    bool right=true;
    int length;


    qreal m_x;
};

#endif // WATER_H
