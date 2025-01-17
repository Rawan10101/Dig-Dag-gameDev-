#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include<globals.h>
#include <QMainWindow>
#include <QGraphicsView>
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QGraphicsScene>
#include <QProgressBar>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include "player.h"
#include "enemy.h"
#include "map.h"
#include <QThread>
#include "house.h"
#include "qlabel.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include "player.h"
#include "woodenboxes.h"
#include "rockboxes.h"
#include <QPixmap>
#include "coin.h"
#include "loading.h"
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGraphicsView>
#include <QProgressBar>
#include<QPushButton>
#include "map.h"
#include "loading.h"
#include <QBrush>
#include<QAudioOutput>
#include<QMediaPlayer>
#include "diamond.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow(QWidget* parent, int initialLevel);
    ~MainWindow();
    Player* player;
    void updateEnemyPosition();
    int money;
    QProgressBar *progressBar;
    QProgressBar *healthBar;
    QLabel *progressLabel;
    QLabel *healthlabel;
    void updateProgressBar();
    void restartGame();
    bool hasWon = false;
    void startRockFallTimer();
    void checkRocksForFalling();
    void updateHealthBar();
    void starthealthbarTimer();
    void loadGrid(const QString &fileName);
    int level;
    void startNextLevel();
    void UpdateLevel(int level);
    bool isCooldown;    // Cooldown state
    QTimer *cooldownTimer; // Timer to manage cooldown
    void resetCooldown();
    void  takeDamage(int);
    bool lost;
    void clearGameObjects();

    void checkPlayerCollisions();
     int getLevel();
    void shop();
     house* houseObject;
    int diamonds;
 QGraphicsScene *scene;
    QTimer *countdownTimer;
 bool isPaused;

     Diamond* diamond;
private:
    Ui::MainWindow *ui;
    QGraphicsView *view;

    QProgressBar* coinsbar;
    Enemy* enemy;
    double tileWidth, tileHeight;
    int w,h;
    bool hasShownMap;
    Map* map;
    QThread myThread;
    QPushButton *pauseButton;
    QTimer* gameUpdateTimer;
    QList<Enemy*> enemies;
 QProgressBar* diamondBar;
    QLabel* diamondlabel;
    void updateCountdown();
    QLabel *timerLabel;
    int remainingTime;
    QTimer *enemyTimer;
    QTimer* timer1;
    QTimer *htimer;
    QTimer* levelTimer;
    QTimer* collisionTimer;
    QPushButton* shopButton;
    void setPlayer(Player* player);
    Map* shopWindow;
    void restartTimer(int);
    void resetTimerForLevel();
    void updateDiamondBar();
    static QMediaPlayer* backgroundMusicPlayer;
    static QAudioOutput* audioOutput;
private slots:

    void togglePause();
public slots:
    void Lostfunc();
    void updatePlayerStats(int health, int diamonds);
};
#endif // MAINWINDOW_H
