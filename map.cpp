#include "map.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDebug>
#include "mainwindow.h"
#include <QMessageBox>
Map::Map(Player* player)
    : QWidget(), player(player)
{
    setWindowTitle("Shop");

    setStyleSheet("background-image: url('D:/Final Applied DS project/fc900857-3800-4ed2-95ff-c34d3cdd7d33.jpeg');"
                  "background-position: center;"
                  "background-repeat: no-repeat;"
                  "background-attachment: fixed;");

    QLabel* healthImageLabel = new QLabel(this);
    QPixmap healthImage("C:/path_to_health_image.jpg");
    healthImageLabel->setPixmap(healthImage);
    healthImageLabel->setScaledContents(true);

    QLabel* speedImageLabel = new QLabel(this);
    QPixmap speedImage("C:/path_to_speed_image.jpg");
    speedImageLabel->setPixmap(speedImage);
    speedImageLabel->setScaledContents(true);

    QPushButton* playerHealth = new QPushButton("Upgrade Player Health", this);
    playerHealth->setFixedSize(150, 40);

    QPushButton* playerSpeed = new QPushButton("Upgrade Player Speed", this);
    playerSpeed->setFixedSize(150, 40);


    coins = new QLabel(this);
    coins->setText("Your Diamond is: " + QString::number(player->getDiamond()));
    coins->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addSpacing(20);
    layout->addWidget(coins);
    layout->addSpacing(20);
    layout->addWidget(healthImageLabel, 0, Qt::AlignCenter);
    layout->addWidget(speedImageLabel, 0, Qt::AlignCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(playerHealth);
    buttonsLayout->addWidget(playerSpeed);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    layout->addLayout(buttonsLayout);

    setLayout(layout);

    connect(playerHealth, &QPushButton::clicked, this, &Map::playerHealthIncrease);
    connect(playerSpeed, &QPushButton::clicked, this, &Map::playerSpeedIncrease);
}

void Map::playerSpeedIncrease()
{
    qDebug() << "Coins: " << player->getDiamond();
    if (player->getDiamond() >= 2) {
        player->increaseSpeed();
        player->deductDiamonds(2);
        coins->setText("Your Diamond is: " + QString::number(player->getDiamond()));

        emit playerStatsUpdated(player->getHealth(), player->getDiamond());
    } else {
        QMessageBox::warning(this, "Insufficient Coins", "You need at least 2 Diamonds to upgrade speed!");
    }
}

void Map::playerHealthIncrease()
{
    if (player->getDiamond() >= 2) {
        player->increaseHealth(2);
        player->deductDiamonds(2);
        coins->setText("Your Diamond is: " + QString::number(player->getDiamond()));

        emit playerStatsUpdated(player->getHealth(), player->getDiamond());
    } else {
        QMessageBox::warning(this, "Insufficient Coins", "You need at least 2 Diamonds to upgrade health!");
    }
}
