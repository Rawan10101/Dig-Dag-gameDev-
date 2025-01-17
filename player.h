#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include<QProgressBar>
#include <QMessageBox>
#include "health.h"
#include <QObject>
#include <QGraphicsScene>

class Player :  public QGraphicsPixmapItem
{

public:
    Player();
    void setInitialPosition(int x, int y);
    void keyPressEvent(QKeyEvent *event) override;
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void setScenePointer(QGraphicsScene* scenePtr);
    bool checkCollisions(int x=0,int y=0);
    QGraphicsScene* scenePointer;
    int  getCoins();
    bool checkAndTriggerRockFall();
    void decreaseHealth(int amount);
    int getHealth() const;
    int health;
     Health* playerHealth;
    bool checkCollisionWithImage(const QGraphicsPixmapItem*);



    void deductCoins(int amount);
    void increaseSpeed();
    void increaseHealth(int amount);
    int getDiamond();
    void deductDiamonds(int amount);
private:
    QPixmap Image;
    QProgressBar* coinsbar;
    int coinscollected;
    bool isPlayerPaused;
    int speed;
    int diamond;
signals:
    void healthChanged(int newHealth);
public slots:
    void setPaused(bool x);

};

#endif // PLAYER_H
