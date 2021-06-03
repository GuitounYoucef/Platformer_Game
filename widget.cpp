#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new MyScene(this);









    scene->addPlatform();
  //  scene->addLine(0,0,800,0,QPen(Qt::black));

    scene->addPlayer(ui->graphicsView);
    scene->addCloud();

    ui->graphicsView->setScene(scene);



}

Widget::~Widget()
{
    delete ui;

}

