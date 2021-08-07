#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new MyScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    scene->newScene();




}

Widget::~Widget()
{
    delete ui;

}

