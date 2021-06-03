#ifndef BRIKS_H
#define BRIKS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include<QParallelAnimationGroup>

class Briks : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)
    qreal m_y;

    qreal m_x;

public:
    explicit Briks(int brikSize); // 1:big 2:small

    qreal y() const;

    qreal x() const;

public slots:
    void setY(qreal y);

    void setX(qreal x);

signals:
private:
    QGraphicsPixmapItem *brik;


};

#endif // BRIKS_H
