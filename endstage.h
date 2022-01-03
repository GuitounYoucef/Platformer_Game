#ifndef ENDSTAGE_H
#define ENDSTAGE_H
#include<QGraphicsPixmapItem>
#include<QObject>
#include"myscene.h"

class EndStage :public QObject,  public QGraphicsPixmapItem

{
public:
    EndStage(int xpos,int ypos,QString nextmapPath,MyScene *scene);
    void NextMap();
    void setNextmapPath(QString nextmapPath);
    QString getNextmapPath();
    void ReturnToCheckPoint(QString mapPath);

private:
 QString  nextmapFileLink;
 MyScene *myscene;


};

#endif // ENDSTAGE_H
