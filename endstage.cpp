#include "endstage.h"

EndStage::EndStage(int xpos,int ypos,QString nextmapPath,MyScene *scene)
{
myscene=scene;
setPixmap(QPixmap(":/images/metalBlokEndStage.png"));
setPos(xpos,ypos);
setNextmapPath(nextmapPath);
}

void EndStage::setNextmapPath(QString nextmapPath)
{
    nextmapFileLink=nextmapPath;
}

QString EndStage::getNextmapPath()
{
    return nextmapFileLink;
}

void EndStage::NextMap()
{
   myscene->removeAllitemes();
   myscene->loadMapFromFile(getNextmapPath());
}
