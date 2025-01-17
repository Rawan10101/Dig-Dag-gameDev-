#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include "player.h"
class QPushButton;
class QLabel;
class QVBoxLayout;

class Map : public QWidget {

    Q_OBJECT

public:
    explicit Map(Player* player);
    QLabel* coins;

public slots:
    void  playerSpeedIncrease();
    void playerHealthIncrease();

private:
    QPixmap backgroundImage;
    Player* player;
signals:
    void playerStatsUpdated(int health, int diamond);
};

#endif // MAP_H
