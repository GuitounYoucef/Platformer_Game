#ifndef HALFCASTLERIGHT_H
#define HALFCASTLERIGHT_H

#include <QObject>
#include <QGraphicsPixmapItem>

class HalfCastleRight : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit HalfCastleRight(int xpos,int ypos);

signals:

};

#endif // HALFCASTLERIGHT_H
