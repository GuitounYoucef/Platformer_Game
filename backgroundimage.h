#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class BackgroundImage : public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    qreal m_x;

public:
    explicit BackgroundImage(QObject *parent = nullptr);
    void setImageFile(QString filePath);

    qreal x() const;

public slots:
    void setX(qreal x);

signals:

};

#endif // BACKGROUNDIMAGE_H
