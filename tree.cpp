#include "tree.h"
#include<QRandomGenerator>

Tree::Tree(int xpos,int ypos)
{
int x = (QRandomGenerator::global()->generate()) %6;

switch (x) {
case 0:{
    setPixmap(QPixmap(":/images/tree1.png"));
    break;}
case 1:{
    setPixmap(QPixmap(":/images/tree2.png"));
    break;}
case 2:{
    setPixmap(QPixmap(":/images/tree3.png"));
    break;}
case 3: {
    setPixmap(QPixmap(":/images/tree4.png"));
    break;}
case 4: {
    setPixmap(QPixmap(":/images/tree5.png"));
    break;}
case 5: {
    setPixmap(QPixmap(":/images/tree6.png"));
    break;}
case 6: {
    setPixmap(QPixmap(":/images/tree7.png"));
    break;}
case 7: {
    setPixmap(QPixmap(":/images/tree8.png"));
    break;}
}

setX(xpos);
setY(ypos-pixmap().height()+50);


setZValue(-7);
}
