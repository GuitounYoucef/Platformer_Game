#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItemGroup>

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
#include"map.h"



class MyScene : public QGraphicsScene
{
    Q_OBJECT


public:
    explicit MyScene(QGraphicsView *graphicsView);
    void addPlayer(int xpos,int ypos);
    void addPlatform(int xpos,int ypos,int type);
    void addCloud();
    void newScene();
    void newMap(int width,int height,QString fileName);
    void loadMapFromFile(QString filePath);
    void removeAllitemes();
    void ReturnToCheckPoint();

    QGraphicsView *ScenegraphicsView;

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
 Coin *coin;
 Platform *questbox;
 Piranha *piranha;
 Pipe *pipe;
 Goomba *goomba[10];
 Koopa *koopa;
 Spiny *spiny;
 QString mapPath=":/mario1.txt";


 QTimer *timer;
 QTimer *checkPointtimer;
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
