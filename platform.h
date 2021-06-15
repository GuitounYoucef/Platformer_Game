#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include<QParallelAnimationGroup>
#include<QSequentialAnimationGroup>
#include<QMediaPlayer>
#include"briks.h"
#include"questbox.h"
#include"mushroom.h"
#include"inanimateobject.h"

class Platform :    public InanimateObject
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Platform(int platformType,int x,int y);  //1:ground   2:air
    int getPlatformType();
    void destroyPlatform();
    void Touched();
    QGraphicsPixmapItem *Graphicsplateform;

    qreal y() const;

    qreal x() const;

public slots:
    void setY(qreal y);

    void setX(qreal x);

signals:

private:


    Questbox *questbox;
    Mushroom *mushroom;

    Briks * briksArray[15];
    QPropertyAnimation * yAnimationArrayUp[15];
    QPropertyAnimation * yAnimationArrayDown[15];
    QPropertyAnimation * xAnimationArray[15];
    QSequentialAnimationGroup * yAnimation[15];

    QPropertyAnimation * touchedAnimationUp;
    QPropertyAnimation * touchedAnimationDown;
    QSequentialAnimationGroup * SeqtouchedAnimation;

    int numberItem=1;

    QMediaPlayer *collapseSound;


    QParallelAnimationGroup * BrikAnimation;



    int xPos,yPos;

    int typePlatform;
    QTimer *firstToutchtimer;
    QTimer *timerStartTouch;

    qreal m_y;
    qreal m_x;
};

#endif // PLATFORM_H
