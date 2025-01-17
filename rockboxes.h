#ifndef ROCKBOXES_H
#define ROCKBOXES_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
class RockBoxes : public QGraphicsPixmapItem,QObject
{

public:
    RockBoxes();
    void fall();
    bool checkForWoodenBoxBelow();
    void uphealth();

signals:
   // void rockHitPlayer();
    bool rockfall;

};

#endif // ROCKBOXES_H
