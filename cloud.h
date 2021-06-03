#ifndef CLOUD_H
#define CLOUD_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Cloud : public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    qreal m_x;

public:
    explicit Cloud(int xAxe,int yAxe);

    qreal x() const;

    qreal y() const;

public slots:
    void setX(qreal x);

    void setY(qreal y);

signals:

private:
QPropertyAnimation * xAnimation;

qreal m_y;
};

#endif // CLOUD_H
