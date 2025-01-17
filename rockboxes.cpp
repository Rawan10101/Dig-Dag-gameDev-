#include "rockboxes.h"
#include "woodenboxes.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "coin.h"
#include "player.h"
#include <QMainWindow>
#include <QApplication>
#include "mainwindow.h"
#include <QTimer>
RockBoxes::RockBoxes(){

}

void RockBoxes::fall() {
    QPointF currentPos = pos();
    qDebug() << "Current position before fall:" << currentPos;

    MainWindow* mainWindow = dynamic_cast<MainWindow*>(QApplication::activeWindow());
    if (!mainWindow) {
        qDebug() << "Error: MainWindow is null!";
        return;
    }

    if (!checkForWoodenBoxBelow()) {
        if (y() + pixmap().height() + 10 <= mainWindow->scene->height()) {
            setPos(x(), y() + 10);
            qDebug() << "Rock moved down to:" << pos();
        }
    } else {
        qDebug() << "Collision detected, rock did not fall";
    }
}


bool RockBoxes::checkForWoodenBoxBelow() {  //to avoid error not put two rcks above each other
    QPointF rockPos = pos();
    qreal rockX = rockPos.x();
    qreal rockY = rockPos.y();


    QList<QGraphicsItem *> itemsBelow = scene()->items(QRectF(rockX, rockY + 10, 20, 20));


    for (QGraphicsItem *item : itemsBelow) {
        if (WoodenBoxes* woodenBox = dynamic_cast<WoodenBoxes*>(item) ) {
            qDebug() << "Collided with WoodenBox at position:" << woodenBox->pos();
            return true;
        }
    }
    // for (QGraphicsItem *item : itemsBelow) {
    //     if (RockBoxes* rock = dynamic_cast<RockBoxes*>(item) ) {
    //         qDebug() << "Collided with WoodenBox at position:" << rock->pos();
    //         return true;
    //     }
    // }

    for (QGraphicsItem *item : itemsBelow) {
        if (coin* Coin = dynamic_cast<coin*>(item)) {
            qDebug() << "Collided with Coin at position:" << Coin->pos();
            return true;
        }
    }

    for (QGraphicsItem *item : itemsBelow) {


        if (Player* player = dynamic_cast<Player*>(item)) {
            qDebug() << "Collided with player at position:" << player->pos();
            MainWindow* mainWindow = dynamic_cast<MainWindow*>(QApplication::activeWindow());
            if (mainWindow) {
                mainWindow->takeDamage(20);
            } else {
                qDebug() << "MainWindow not found!";
            }
            return true;
        }

    }
    for (QGraphicsItem *item : itemsBelow) {


        if (Enemy* enemy = dynamic_cast<Enemy*>(item)) {
            qDebug() << "Collided with player at position:" << enemy->pos();
            MainWindow* mainWindow = dynamic_cast<MainWindow*>(QApplication::activeWindow());
            if (mainWindow) {
                if (mainWindow->scene) {
                        mainWindow->scene->removeItem(item);
                        delete item;
                }
            }
            else {
                qDebug() << "MainWindow not found!";
            }
            return true;
        }

    }

    return false;
}
void RockBoxes::uphealth() {
    MainWindow* mainWindow = dynamic_cast<MainWindow*>(QApplication::activeWindow());
    if (mainWindow) {
        mainWindow->updateHealthBar();
    } else {
        qDebug() << "MainWindow not found!";
    }
}

