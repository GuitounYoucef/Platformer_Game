#include "myscene.h"
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QDebug>
#include <QScrollBar>





MyScene::MyScene(QObject *parent) : QGraphicsScene(-950,-400,10000,720, parent)

{
    pixItem = new QGraphicsPixmapItem(QPixmap(":/images/BackgroundImage.png"));
//    pixItem->setZValue(-12);
//    addItem(pixItem);
    background= new BackgroundImage();
    background->setPos(-950,-600);
    background->setX(-950);
    addItem(background);


//    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    graphicsView->setScene(this);

//    yPos=graphicsView->horizontalScrollBar();

//    yPos->setValue(-950);
    QLinearGradient linearGrad(QPointF(0, -500), QPointF(0, 500));
    linearGrad.setColorAt(0, qRgba(0, 130, 190,250));
    linearGrad.setColorAt(1, Qt::white);

     setBackgroundBrush(linearGrad);


//    ScrollAnimation = new QPropertyAnimation(yPos,"value");



    //scroll->setValue(100);

  //  addToGroup(pixItem);

     backgroundMusic=new QMediaPlayer();
     backgroundMusic->setMedia(QUrl("qrc:/sound/sound/overworld.ogg"));
     backgroundMusic->setVolume(50);
   //  backgroundMusic->play();


}

void MyScene::addPlayer(QGraphicsView *graphicsView)
{
    player = new Player(graphicsView,this,background);
    player->setPos(400,100);
    pixItem->setPos(-pixItem->boundingRect().width()/2,-pixItem->boundingRect().height()/2);


    addItem(player);






}

void MyScene::addPlatform()
{
//    platform = new Platform();
//    platform->setPos(100,-160);
//    addItem(platform);


//    platform = new Platform(2,200,-150);
//    addItem(platform);
    int nextPlatform=-1000;
    for (int i=1; i<=10 ;i++ ) {




    platform = new Platform(1,nextPlatform,300);
    addItem(platform);
    nextPlatform=nextPlatform+platform->Graphicsplateform->pixmap().width();





     }
    nextPlatform=-500;
    for (int i=1; i<=10 ;i++ ) {

     if (i%2==0)
     {
    blockBrikcs =new Platform(3,nextPlatform,-150);
    addItem(blockBrikcs);

     }else
    {

    questbox= new Platform(4,nextPlatform,-150);
    addItem(questbox);
     }
     nextPlatform=nextPlatform+64;
}
    for (int i=1; i<=5 ;i++ ) {
    tree= new Tree(10000);
    addItem(tree);
    }

    for (int i=1; i<=5 ;i++ ) {
    coin= new Coin(i*150,-250);
    addItem(coin);
    }

    for (int i=1; i<=2 ;i++ ) {
    pipe= new Pipe(2);
    pipe->setPos(i*1000,80);
    addItem(pipe);
    }

    goomba= new Goomba();
    goomba->setPos(650,-350);
    addItem(goomba);
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
          player->walk(0,background,true);
          break;}
      case Qt::Key_Left :
    {
       player->walk(1,background,true);
       break;
    }
    case Qt::Key_Up :
     player->Jump();
     break;
    case Qt::Key_Space :
     player->setMarioSize(1);
     break;
    case Qt::Key_Control :
     player->setMarioSize(0);
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
