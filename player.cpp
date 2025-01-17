#include "player.h"
#include "qaudiooutput.h"
#include "qmediaplayer.h"
#include "woodenboxes.h"
#include <QGraphicsScene>
#include "rockboxes.h"
#include <QKeyEvent>
#include "coin.h"
#include "loading.h"
#include "health.h"
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "house.h"
#include "mainwindow.h"
#include "enemy.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>
#include "diamond.h"
Player::Player() {
    Image = QPixmap(":/new/prefix1/caveman transformed left.png");
    setPixmap(Image);
    setPos(0, 0);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    coinscollected = 0;
    health=100;
      playerHealth = new Health();
    speed=10;
      diamond=0;
}

void Player::setInitialPosition(int x, int y) {
    setPos(x, y);
}

void Player::setScenePointer(QGraphicsScene* scenePtr) {
    scenePointer = scenePtr;

}


void Player::moveLeft() {
   ;
    Image = QPixmap(":/new/prefix1/caveman transformed left.png");
    setPixmap(Image);

    if (x() > 0) {
        if (!checkCollisions(-10, 0))
            return;
        setPos(x() - speed, y());
    }
}

void Player::moveRight() {

    Image = QPixmap(":/new/prefix1/caveman transformed.png");
    setPixmap(Image);
    QRectF sceneRect = scenePointer->sceneRect();
    if (x() + pixmap().width() <= sceneRect.width()) {
        if (!checkCollisions(10, 0))
            return;
        setPos(x() + speed, y());
    }
}
void Player::moveUp() {

    if (y() > 0) {
        if (!checkCollisions(0, -10))
            return;
        setPos(x(), y() - speed);
    }
}

void Player::moveDown() {

    QRectF sceneRect = scenePointer->sceneRect();

    if (y() + pixmap().height() + 10 <= sceneRect.height()) {  // Bottom boundary check
        if (!checkCollisions(0, 10))
            return;
        setPos(x(), y() + speed);
    }
}

void Player::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        moveLeft();
        break;
    case Qt::Key_Right:
        moveRight();
        break;
    case Qt::Key_Up:
        moveUp();
        break;
    case Qt::Key_Down:
        moveDown();
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(event);
        break;
    }
}

bool Player::checkCollisions(int dx, int dy) {
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        if (typeid(*item) == typeid(WoodenBoxes)) {
            qDebug() << "Collided with WoodenBox at position:" << item->pos();
            if (scene()) {
                scene()->removeItem(item);
                delete item;

                return true;
            }
        } else if (typeid(*item) == typeid(RockBoxes)) {
            qDebug() << "Collided with RockBox at position:" << item->pos();


            QPointF playerPos = pos();
            QPointF itemPos = item->pos();
            qreal xDiff = itemPos.x() - playerPos.x();
            qreal yDiff = itemPos.y() - playerPos.y();

            if ((dx > 0 && xDiff > 0) ||
                (dx < 0 && xDiff < 0) ||
                (dy > 0 && yDiff > 0) ||
                (dy < 0 && yDiff < 0)) {
                return false;
            } else {
                QMediaPlayer *player = new QMediaPlayer();
                QAudioOutput *audioOutput = new QAudioOutput();
                player->setAudioOutput(audioOutput);
                player->setSource(QUrl("qrc:/new/prefix1/hit-rock-01-266301.mp3")); // Set sound file
                audioOutput->setVolume(50);
                player->play();
                return true;
            }
        } else if (typeid(*item) == typeid(coin)) {
            qDebug() << "Collided with coin at position:" << item->pos();
            if (scene()) {
                QMediaPlayer *player = new QMediaPlayer();
                QAudioOutput *audioOutput = new QAudioOutput();
                player->setAudioOutput(audioOutput);
                player->setSource(QUrl("qrc:/new/prefix1/eating-sound-effect-36186.mp3")); // Set sound file
                audioOutput->setVolume(50);

                player->play();
                scene()->removeItem(item);
                delete item;
                coinscollected++;
                qDebug() << "Coin Collected:" << coinscollected;
                return true;
            }

        }
        else if (typeid(*item) == typeid(Diamond)) {
            qDebug() << "Collided with diamond at position:" << item->pos();
            if (scene()) {
                QMediaPlayer *player = new QMediaPlayer();
                QAudioOutput *audioOutput = new QAudioOutput();
                player->setAudioOutput(audioOutput);
                player->setSource(QUrl("qrc:/new/prefix1/mixkit-winning-a-coin-video-game-2069.wav")); // Set sound file
                audioOutput->setVolume(50);

                player->play();
                scene()->removeItem(item);
                delete item;
                diamond++;
                qDebug() << "diamond Collected:" << diamond;
                return true;
            }

        }
        else if (typeid(*item) == typeid(Enemy)) {
            qDebug() << "Collided with coin at position:" << item->pos();
            if (scene()) {
                MainWindow* mainWindow = dynamic_cast<MainWindow*>(QApplication::activeWindow());
                if (mainWindow) {
                    QMediaPlayer *player = new QMediaPlayer();
                    QAudioOutput *audioOutput = new QAudioOutput();
                    player->setAudioOutput(audioOutput);               // Associate the audio output
                    player->setSource(QUrl("qrc:/new/prefix1/zombie-bite-96528.mp3")); // Set sound file
                    audioOutput->setVolume(50);

                    // Play the sound
                    player->play();
                    mainWindow->takeDamage(10);
                } else {
                    qDebug() << "MainWindow not found!";
                }
                return true;
            }

        }


    }
    return true;
}
bool Player::checkAndTriggerRockFall() {
}
int Player::getDiamond()
{
    return diamond;
}
void Player::deductDiamonds(int amount) {
    diamond -= amount;
}
int Player::getCoins() {
    return coinscollected;
}
int Player::getHealth() const{
    return health;
}

void Player::deductCoins(int amount) {
    coinscollected -= amount;
}

void Player::increaseSpeed() {
    speed += 5;
    qDebug() << "Player speed increased to " << speed;
}

void Player::increaseHealth(int amount) {
    health += amount;
    qDebug() << "Player health increased to " << health;
}

