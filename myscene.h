#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QTimer>
#include <QObject>
#include<QKeyEvent>
#include<QMediaPlayer>


#include"player.h"
#include"bullet.h"
#include"platform.h"
#include"cloud.h"
#include"backgroundimage.h"
#include"tree.h"
#include "coin.h"
#include "questbox.h"
#include "piranha.h"
#include "pipe.h"
#include "goomba.h"
#include "koopa.h"
#include "spiny.h"


class MyScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit MyScene(QObject *parent = 0);
    void addPlayer(QGraphicsView *graphicsView);
    void addPlatform();
    void addCloud();


    qreal x() const;

public slots:
    void setX(qreal x);

signals:

private:
 QScrollBar *scroll;
 Player *player;
 Platform *platform;
 Platform *platform2;
 Platform *platform3;
 Cloud *cloud1;
 BackgroundImage *background;
 Platform *blockBrikcs;
 Platform *blockMetal;
 Tree * tree;
 Coin *coin;
 Platform *questbox;
 Piranha *piranha;
 Pipe *pipe;
 Goomba *goomba[10];
 Koopa *koopa;
 Spiny *spiny;


 QTimer *timer;
 QScrollBar* yPos;

 QPropertyAnimation * ScrollAnimation;
 QPropertyAnimation * pixItemAnimation;

 void moveScene(int dist);
 QGraphicsPixmapItem * pixItem;
 QPropertyAnimation * xAnimation;
 bool keypressed=false;



 // QGraphicsScene interface
 qreal m_x;

protected:
 void keyPressEvent(QKeyEvent *event);

 // QGraphicsScene interface
protected:
 void keyReleaseEvent(QKeyEvent *event);
};

#endif // MYSCENE_H
