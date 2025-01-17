#include "enemy.h"
#include "player.h"
#include <QList>
#include <QGraphicsItem>
#include <cmath>
#include <unordered_map>
#include "woodenboxes.h"
#include "rockboxes.h"
#include "coin.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QPointF>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include "mainwindow.h"

struct QPointFHash {
    std::size_t operator()(const QPointF& point) const {
        return std::hash<qreal>()(point.x()) ^ (std::hash<qreal>()(point.y()) << 1);
    }
};

struct Node {
    QPointF position;
    float gCost;
    float hCost;
    float fCost;
    Node* parent;


    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

Enemy::Enemy() : scenePointer(nullptr) {
      health=3;

}

void Enemy::setScenePointer(QGraphicsScene* scenePtr) {
    scenePointer = scenePtr;
}

void Enemy::followPath() {
    if (path.isEmpty()) {
        qWarning() << "No path to follow!";
        return;
    }

    int steps = speed;
    while (steps-- > 0 && !path.isEmpty()) {
        QPointF nextPos = path.takeFirst();
        setPos(nextPos);
        qDebug() << "Moving to: " << nextPos<<" with speed "<<speed;
    }
}

void Enemy::handleCollisions() {
    QList<QGraphicsItem*> collidingItems = this->collidingItems();

    for (QGraphicsItem* item : collidingItems) {
        if (dynamic_cast<WoodenBoxes*>(item) || dynamic_cast<RockBoxes*>(item) || dynamic_cast<coin*>(item)) {
            qDebug() << "Collision detected with" << item;
            setPos(previousPosition);
            return;
        }
    }
}

void Enemy::moveTowardsPlayer(Player* player) {
    if (!player) {
        qDebug() << "Player is null!";
        return;
    }


    static std::unordered_map<Enemy*, int> enemyFrameCounts;

    if (enemyFrameCounts.find(this) == enemyFrameCounts.end()) {
        enemyFrameCounts[this] = 0;
    }


    if (++enemyFrameCounts[this] % 10 == 0) {
        qDebug() << "Calculating path for this enemy";
        calculatePath(player->pos());
    }


    followPath();
}

void Enemy::calculatePath(QPointF playerPos) {
    if (!scenePointer) {
        qWarning() << "Scene pointer is null! Cannot calculate path.";
        return;
    }


    std::unordered_map<QPointF, float, QPointFHash> fCostMap;
    std::unordered_map<QPointF, QPointF, QPointFHash> cameFrom;
    std::unordered_set<QPointF, QPointFHash> closedSet;

    auto compare = [](const Node& a, const Node& b) { return a.fCost > b.fCost; };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> openList(compare);

    QPointF startPos = pos();
    fCostMap[startPos] = heuristic(startPos, playerPos);

    openList.push({startPos, 0.0f, heuristic(startPos, playerPos), fCostMap[startPos], nullptr});

    QList<QPointF> directions = {QPointF(-1, 0), QPointF(1, 0), QPointF(0, -1), QPointF(0, 1)};

    while (!openList.empty()) {
        QPointF currentPos = openList.top().position;
        openList.pop();

        if (currentPos == playerPos) {
            path.clear();
            while (cameFrom.find(currentPos) != cameFrom.end()) {
                path.prepend(currentPos);
                currentPos = cameFrom[currentPos];
            }
            qDebug() << "Path found!";
            return;
        }

        closedSet.insert(currentPos);

        for (const QPointF& direction : directions) {
            QPointF neighborPos = currentPos + direction;


            if (neighborPos.x() < 0 || neighborPos.y() < 0 || neighborPos.x() >= scenePointer->width() || neighborPos.y() >= scenePointer->height()) {
                continue;
            }

            bool isWalkable = true;
            for (QGraphicsItem* item : scenePointer->items(neighborPos)) {
                if (dynamic_cast<WoodenBoxes*>(item) || dynamic_cast<RockBoxes*>(item) || dynamic_cast<coin*>(item)) {
                    isWalkable = false;
                    break;
                }
            }
            if (!isWalkable || closedSet.count(neighborPos)) continue;

            float tentativeGCost = fCostMap[currentPos] + 1.0f;

            if (fCostMap.find(neighborPos) == fCostMap.end() || tentativeGCost < fCostMap[neighborPos]) {
                fCostMap[neighborPos] = tentativeGCost;
                float hCost = heuristic(neighborPos, playerPos);
                openList.push({neighborPos, tentativeGCost, hCost, tentativeGCost + hCost, nullptr});
                cameFrom[neighborPos] = currentPos;
            }
        }
    }

    qWarning() << "No path to player found!";
}

float Enemy::heuristic(const QPointF& a, const QPointF& b) {
    return std::abs(a.x() - b.x()) + std::abs(a.y() - b.y());
}
