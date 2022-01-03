#ifndef MAP_H
#define MAP_H

#include <QObject>
#include<QGraphicsScene>

class Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(QObject *parent = nullptr);
    void openMap(QString Filelink);
    void newMap(int width,int height,QString fileName);
    void loadMapFromFile(QGraphicsScene *scene, QString fileName);

signals:

};

#endif // MAP_H
