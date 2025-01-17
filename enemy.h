#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include "player.h"
class Enemy :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();
    void setScenePointer(QGraphicsScene* scenePtr);
    void moveTowardsPlayer(Player* player);
    void calculatePath(QPointF playerPos);
    void followPath();
    void handleCollisions();
    int health;
    int speed;
    void setPaused(bool paused);


private:
    QGraphicsScene* scenePointer;
    QList<QPointF> path;
    QTimer *movementTimer;
    bool isPaused = false;

    QPointF previousPosition;
    float heuristic(const QPointF& a, const QPointF& b);

};


#endif // ENEMY_H
