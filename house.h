
#ifndef HOUSE_H
#define HOUSE_H

#include <QGraphicsItem>
#include "map.h"
#include "player.h"


class house : public QGraphicsPixmapItem {
public:
    house(/*MainWindow* mainwindow*/);
  void checkCollisionwithPlayer(bool hasWon,int nextLevel);
private:
     //MainWindow* mainWindow;
     bool mapWindowShown = false;
    Map* map = nullptr;
};

#endif // HOUSE_H
