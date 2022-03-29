#include "myscene.h"
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QDebug>
#include <QScrollBar>
#include <QtAlgorithms>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickView>

#include <QQmlApplicationEngine>
#include<QThread>

#include"castle.h"
#include"endstage.h"
#include"water.h"
#include "lake.h"
#include "tree.h"
#include "koopa.h"





MyScene::MyScene(QGraphicsView *graphicsView)

{
    ScenegraphicsView=graphicsView;




    pixItem = new QGraphicsPixmapItem(QPixmap(":/images/BackgroundImage.png"));
//    pixItem->setZValue(-12);
//    addItem(pixItem);
    background= new BackgroundImage();
    background->setPos(-950,-600);
    background->setX(-950);
 //   addItem(background);


//    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    graphicsView->setScene(this);

//    yPos=graphicsView->horizontalScrollBar();

//    yPos->setValue(-950);
    QLinearGradient linearGrad(QPointF(0, -500), QPointF(0, 500));
    linearGrad.setColorAt(0, qRgba(0, 130, 190,250));
    linearGrad.setColorAt(1, Qt::white);

     setBackgroundBrush(linearGrad);
      addPlayer(400,-600);



//    ScrollAnimation = new QPropertyAnimation(yPos,"value");



    //scroll->setValue(100);

  //  addToGroup(pixItem);




}

void MyScene::addPlayer(int xpos,int ypos)
{
    player = new Player(ScenegraphicsView,this,background);
    player->setX(xpos);
    player->setY(ypos);

    checkPointtimer= new QTimer();

    addItem(player);
    connect(player,&Player::RetCheckPoint,[=](){
        ReturnToCheckPoint();
   });




}

void MyScene::addPlatform(int xpos,int ypos,int type)
{
    Platform *platform = new Platform(type,xpos,ypos);
    addItem(platform);
}

void MyScene::addCloud()
{
    int nextPlatform=0;
    for (int i=1; i<5 ;i++ ){

    cloud1 =new Cloud(nextPlatform,-1150);
    //cloud1->setPos(nextPlatform,-850);
    nextPlatform=nextPlatform+1200;

    addItem(cloud1);
    }





}

void MyScene::newScene()
{
loadMapFromFile(mapPath);

}

qreal MyScene::x() const
{
    return m_x;
}

void MyScene::setX(qreal x)
{
    m_x = x;
    qDebug()<<m_x;
}



void MyScene::keyPressEvent(QKeyEvent *event)
{

    keypressed=true;
    switch(event->key()) {
       case Qt::Key_Right :
    {
          player->walk(0,background);
          if (player->backgroundMusic->PausedState){
              player->backgroundMusic->play();
          }
          break;}
      case Qt::Key_Left :
    {
       player->walk(1,background);

       break;
    }
    case Qt::Key_Up :
     player->Jump();

     break;
    case Qt::Key_Down :
       player->shootFire();

     break;
    case Qt::Key_Space :
     player->setMarioSize(1);
     break;
    case Qt::Key_Control :
        //player->setMarioSize(0);
        player->shootFire();
     break;

    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {

       case Qt::Key_Right :
         {
          player->stopWalking();
          break;
         }
    case Qt::Key_Left :
      {
       player->stopWalking();
       break;
      }
    }
}
void MyScene::newMap(int width, int height, QString fileName)
{
    QFile mapFile(fileName);
    if(mapFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&mapFile);
        out<<width<<" ";
        out<<height<<" "<<"\n";
        for(int i=1; i<=height; i++)
        {
            for(int j=1; j<=width; j++)
            out<<"00 ";
            out<<"\n";
        }

    }
    mapFile.close();
}

void MyScene::loadMapFromFile(QString filePath)
{
   //qDeleteAll(items());
    //addItem(player);
    mapPath=filePath;




    QFile file_read(filePath);

    if(file_read.open(QIODevice::ReadOnly))
    {

        QTextStream stream(&file_read);
        while(!file_read.atEnd())
        {
            QString buf;
            QStringList list = stream.readAll().split(" ");
            QListIterator<QString> li(list);

            int width=li.next().toInt();
            int height=li.next().toInt();

            setSceneRect(-900,-900,width*64,height*64);
            QString nextmapPath=li.next();
            QString backgroundPath=li.next();
//            background->setImageFile(backgroundPath);
//            background->setPos(-950,-600);
//            background->setX(-950);
//            background->setOpacity(0.90);
            qDebug()<<width<<height;

            for (int i=1;i<=height ;i++ ) {
                for (int j=1;j<=width ;j++ ) {
                    buf=li.next();
                    if (buf=="PL")
                    {


                      // player->setPos(j*64-1500,i*64-1000);
                    }
                    else
                    if (buf=="P1")
                    {
                        Platform *platform = new Platform(1,j*64-1500,i*64-1000);
                        addItem(platform);
                    }
                    else
                        if (buf=="P3")
                        {
                            Platform *platform = new Platform(3,j*64-1500,i*64-1000);
                            addItem(platform);
                        }
                        else
                            if (buf=="P4")
                            {
                                Platform *platform = new Platform(4,j*64-1500,i*64-1000);
                                addItem(platform);
                            }
                            else
                                if (buf=="CO")
                                {
                                    Coin *coin = new Coin(j*64-1500,i*64-1000);
                                    addItem(coin);
                                }
                                else
                                    if (buf=="p2")
                                    {
                                        Pipe *pipe = new Pipe(2);
                                        pipe->setPos(j*64-1500,i*64-1150);
                                        addItem(pipe);
                                    }
                                    else
                                        if (buf=="P5")
                                        {
                                            Platform *platform = new Platform(5,j*64-1500,i*64-1000);
                                            addItem(platform);
                                        }
                                        else
                                            if (buf=="P6")
                                            {
                                                Platform *platform = new Platform(6,j*64-1500,i*64-1000);
                                                addItem(platform);
                                            }
                                        else
                                                if (buf=="P7")
                                                {
                                                    Platform *platform = new Platform(7,j*64-1500,i*64-1000);
                                                    addItem(platform);
                                                }
                                                else
                                            if (buf=="GM")
                                            {
                                                Goomba *goomba= new Goomba(j*64-1500,i*64-1000);
                                                addItem(goomba);

                                            }
                                            else
                                                if (buf=="KP")
                                                {
                                                    Koopa *koopa= new Koopa(j*64-1500,i*64-1000);
                                                    addItem(koopa);

                                                }
                                                else
                                                if (buf=="CS")
                                                {
                                                    Castle *castle= new Castle(j*64-1500,i*64-1000,1);
                                                    addItem(castle);
                                                    castle= new Castle(j*64-1500,i*64-1000,2);
                                                    addItem(castle);
                                                }
                                                else
                                                    if (buf=="EN")
                                                    {
                                                        EndStage *endStage= new EndStage(j*64-1500,i*64-1000,nextmapPath,this);
                                                        addItem(endStage);
                                                    }
                                                    else
                                                        if (buf=="WT")
                                                        {
                                                            Lake *water= new Lake(j*64-1500,i*64-1000+30,200);
                                                            addItem(water);
                                                        }
                                                        else
                                                            if (buf=="TR")
                                                            {
                                                                Tree *tree= new Tree(j*64-1500,i*64-1000+30);
                                                                addItem(tree);
                                                            }
                                                            else
                                                                if (buf=="CL")
                                                                {
                                                                    Cloud *cloud= new Cloud(j*64-1500,i*64-1000+30);
                                                                    addItem(cloud);
                                                                }




                }

            }
        }
    }

   player->setX(0);
   player->setY(0);


    player->helth=1;


}

void MyScene::removeAllitemes()
{

    QList<QGraphicsItem*> L = items();
    foreach(QGraphicsItem * item,L)
    {
        InanimateObject * inanimateObject =dynamic_cast<InanimateObject*>(item);
        if (inanimateObject){
               removeItem(item);
                inanimateObject->deleteObj();
          }
        QGraphicsPixmapItem * obj =dynamic_cast<QGraphicsPixmapItem*>(item);
        if ((obj)&&(obj!=background) &&(obj!=player)){
               removeItem(item);

          }


    }
}

void MyScene::ReturnToCheckPoint()
{
    removeAllitemes();
    loadMapFromFile(mapPath);
}
