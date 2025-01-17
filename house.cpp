#include "house.h"
#include "player.h"
#include <QDebug>
#include "map.h"
#include "mainwindow.h"

house::house() : QGraphicsPixmapItem(), mapWindowShown(false) {}


void house::checkCollisionwithPlayer(bool hasWon,int nextLevel) {
    if(hasWon){
    MainWindow* nextWindow = new MainWindow(nullptr, nextLevel);
    nextWindow->show();
     qDebug() << "Collision recur";
    hasWon=false;
    }
}
