#include "map.h"
#include<QFile>
#include <QTextStream>
#include"platform.h"
#include"coin.h"
#include"pipe.h"
#include"goomba.h"
#include"castle.h"
#include<QDebug>

Map::Map(QObject *parent) : QObject(parent)
{

}

void Map::openMap(QString Filelink)
{

    // File reading
    QFile file_read(Filelink);
    QVector<QString> array;

    if(file_read.open(QIODevice::ReadOnly))
    {

        QTextStream stream(&file_read);
        while(!file_read.atEnd())
        {
            QString buf;
            QStringList list = stream.readAll().split(" ");
            QListIterator<QString> li(list);
            buf=li.next();
            array.append(buf);
            buf=li.next();
            array.append(buf);

//            while(li.hasNext())
//            {
//                buf=li.next();
//                array.append(buf);
//            }
        }

  }


    QFile Stagefile("C:/Users/guitoun/Documents/Platformer_Game/maps/stage1write.txt");
    if(Stagefile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&Stagefile);
        for(int a{0}; a<array.size(); a++)
        {
            out<<array[a];
            qDebug()<<array[a];
        }
    }
    Stagefile.close();
}

void Map::newMap(int width, int height, QString fileName)
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

void Map::loadMapFromFile(QGraphicsScene *scene, QString filePath)
{


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
            qDebug()<<width<<height;

            for (int i=1;i<=height ;i++ ) {
                for (int j=1;j<=width ;j++ ) {
                    buf=li.next();

                    if (buf=="P1")
                    {
                        Platform *platform = new Platform(1,j*64-1500,i*64-1000);
                        scene->addItem(platform);
                    }
                    else
                        if (buf=="P3")
                        {
                            Platform *platform = new Platform(3,j*64-1500,i*64-1000);
                            scene->addItem(platform);
                        }
                        else
                            if (buf=="P4")
                            {
                                Platform *platform = new Platform(4,j*64-1500,i*64-1000);
                                scene->addItem(platform);
                            }
                            else
                                if (buf=="CO")
                                {
                                    Coin *coin = new Coin(j*64-1500,i*64-1000);
                                    scene->addItem(coin);
                                }
                                else
                                    if (buf=="p2")
                                    {
                                        Pipe *pipe = new Pipe(2);
                                        pipe->setPos(j*64-1500,i*64-1150);
                                        scene->addItem(pipe);
                                    }
                                    else
                                        if (buf=="P5")
                                        {
                                            Platform *platform = new Platform(5,j*64-1500,i*64-1000);
                                            scene->addItem(platform);
                                        }
                                        else
                                            if (buf=="GM")
                                            {
                                                Goomba *goomba= new Goomba(j*64-1500,i*64-1000);
                                                scene->addItem(goomba);
                                            }
                                            else
                                                if (buf=="CS")
                                                {
                                                    Castle *castle= new Castle(j*64-1500,i*64-1000,1);
                                                    scene->addItem(castle);
                                                    castle= new Castle(j*64-1500,i*64-1000,2);
                                                    scene->addItem(castle);
//                                                    castle= new Castle(j*64-1500,i*64-1000,3,2);
//                                                    scene->addItem(castle);
                                                   // HalfCastleRight *HalfCastle2 = new HalfCastleRight(j*64-1500,i*64-1000);

//                                                    HalfCastle2->setX(j*64-1500+192);
//                                                    scene->addItem(HalfCastle2);


                                                }
                }

            }
        }
    }

}


