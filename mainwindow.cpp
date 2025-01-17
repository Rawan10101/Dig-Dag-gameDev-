#include "mainwindow.h"


MainWindow::MainWindow(QWidget* parent, int initialLevel)
    : QMainWindow(parent), level(initialLevel)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
 //   setStyleSheet("background-image: url(:/Background.jpg);");
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    setCentralWidget(view);
    view->setBackgroundBrush(QBrush(QImage(":/new/prefix1/lolo.jpg").scaled(800,600)));

    player = new Player();
    player->setScenePointer(scene);
    //setPlayer(player);

    scene->addItem(player);
    tileWidth = 55;
    tileHeight = 39;
    money=0;
    progressBar = new QProgressBar(this);
    UpdateLevel(level);

    //******************************


     QTimer *timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16);

     diamonds=0;

    progressBar->setRange(0, money);
    progressBar->setValue(0);
    progressBar->setFixedHeight(20);
    progressBar->setStyleSheet("QProgressBar {"
                               "border: 2px solid gray;"
                               "border-radius: 5px;"
                               "background-color: #2c2f38;"
                               "text-align: center;"
                               "}"
                               "QProgressBar::chunk {"
                               "background-color:  green;"
                               "border-radius: 3px;"
                               "}");

    healthBar = new QProgressBar(this);
    healthBar->setRange(0, 100);
    healthBar->setValue(100);
    healthBar->setFixedHeight(20);
    healthBar->setStyleSheet("QProgressBar {"
                             "border: 2px solid gray;"
                             "border-radius: 5px;"
                             "background-color: #2c2f38;"
                             "text-align: center;}"
                             "QProgressBar::chunk {"
                             "background-color: blue;"
                             "border-radius: 3px;}");


    progressLabel = new QLabel("Coins:", this);
    healthlabel = new QLabel("Health:", this);


    diamondBar=new QProgressBar(this);
  // diamondBar->setRange(0, diamonds);
     diamondBar->setValue(100);
     diamondBar->setFixedHeight(20);

    diamondBar->setStyleSheet("QProgressBar {"
                             "border: 2px solid gray;"
                             "border-radius: 5px;"
                             "background-color: #2c2f38;"
                             "text-align: center;}"
                             "QProgressBar::chunk {"
                             "background-color: blue;"
                             "border-radius: 3px;}");
   diamondlabel = new QLabel("Diamond:", this);
    diamondlabel->setContentsMargins(0, 0, 0, 0);
    //diamondBar->setContentsMargins(0, 0, 0, 0);
  //  diamondBar->setStyleSheet("margin: 0; padding: 0;font-weight: bold;");

    QHBoxLayout *barLayout = new QHBoxLayout();
    barLayout->setSpacing(5);

    barLayout->setContentsMargins(10, 10, 10, 10);

    progressLabel->setContentsMargins(0, 0, 0, 0);
    progressBar->setContentsMargins(0, 0, 0, 0);
    healthlabel->setContentsMargins(0, 0, 0, 0);
    healthBar->setContentsMargins(0, 0, 0, 0);

   progressLabel->setStyleSheet("margin: 0; padding: 0;font-weight: bold;");
   healthlabel->setStyleSheet("margin: 0; padding: 0;font-weight: bold;");

    barLayout->addWidget(progressLabel);
    barLayout->addWidget(progressBar);
    barLayout->addWidget(healthlabel);
    barLayout->addWidget(healthBar);
     barLayout->addWidget(diamondlabel);
     barLayout->addWidget(diamondBar);

    progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    healthBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout*barlayout=new QHBoxLayout;
    barLayout->setSpacing(10);
    barLayout->setContentsMargins(10,10,10,10);
barLayout->setStretch(1, 3);
    barLayout->addWidget(progressLabel);
    barLayout->addWidget(progressBar, 1);
    barLayout->addWidget(healthlabel);
    barLayout->addWidget(healthBar, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(barLayout);
    mainLayout->addWidget(view, 10);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    remainingTime = 80;


   // timerLabel = new QLabel(this);
    // timerLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: black;");
    // timerLabel->setText("Time: " + QString::number(remainingTime) + " s");

    // timerLabel->setGeometry(width() / 2 - 50, 10, 100, 30);
    // timerLabel->setAlignment(Qt::AlignCenter);
    // timerLabel->setParent(view);
   // barLayout->addWidget(timerLabel);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);
    countdownTimer->start(1000);

    pauseButton = new QPushButton("Pause", this);
    pauseButton->setGeometry(900, 10, 100, 30);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::togglePause);
    barLayout->addWidget(pauseButton);

    shopButton = new QPushButton("Shop", this);
    shopButton->setGeometry(900, 10, 100, 30);
    connect(shopButton, &QPushButton::clicked, this, &MainWindow::shop);
    barLayout->addWidget(shopButton);

    collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &MainWindow::checkPlayerCollisions);
    collisionTimer->start(100);

    // levelTimer = new QTimer(this);
    // connect(levelTimer, &QTimer::timeout, this, &MainWindow::startNextLevel);
    // qDebug() << "Level Timer Connected. Timeout interval:" << levelTimer->interval();

    // levelTimer->start(100);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgressBar);
    timer->start(100);
     htimer = new QTimer(this);
     connect(htimer, &QTimer::timeout, this, &MainWindow::updateHealthBar);
     timer->start(100);

    enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, this, &MainWindow::updateEnemyPosition);
    enemyTimer->start(100);

    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &MainWindow::checkRocksForFalling);
    timer1->start(100);
    w=55*17;
    h=13*39;
    scene->setSceneRect(0,0,w,h);
    view->setSceneRect(scene->sceneRect());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFocusPolicy(Qt::StrongFocus);

    view->show();
    isCooldown = false;
    cooldownTimer = new QTimer(this);
    cooldownTimer->setSingleShot(true);
    connect(cooldownTimer, &QTimer::timeout, this, &MainWindow::resetCooldown);
    lost=false;
    isPaused=false;
    QTimer* diamondtimer=new QTimer(this);
    connect(diamondtimer, &QTimer::timeout, this, &MainWindow::updateDiamondBar);
    diamondtimer->start(100);
}


void MainWindow::shop()
{
    qDebug() << "Opening Map window";
    shopWindow = new Map(player);
    connect(shopWindow, &Map::playerStatsUpdated, this, &MainWindow::updatePlayerStats);
    shopWindow->show();
}
void MainWindow::togglePause() {
    isPaused=!isPaused;
    if (isPaused) {
        countdownTimer->stop();
        enemyTimer->stop();
        htimer->stop();
        collisionTimer->stop();
        player->hide();

    } else {
        player->show();
        countdownTimer->start(1000);
        enemyTimer->start(100);
        htimer->start(100);
        collisionTimer->start(100);
    }

}


void MainWindow::resetCooldown() {
    isCooldown = false;
}


void MainWindow::takeDamage(int damage) {
    if (isCooldown) {
        return;
    }
    player->health -= damage;
    QMediaPlayer *play = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    play->setAudioOutput(audioOutput);
    play->setSource(QUrl("qrc:/new/prefix1/hit-rock-01-266301.mp3")); // Set sound file
    audioOutput->setVolume(50);
    play->play();
    if (player->health < 0) player->health = 0;

    isCooldown = true;
    updateHealthBar();

    cooldownTimer->start(2000);
}
MainWindow::~MainWindow()
{
    delete player;
    delete cooldownTimer;

    delete ui;
}

void MainWindow::UpdateLevel(int level){
    if (level==1){
        loadGrid(":/new/prefix1/Level one.txt");

    }
    else if (level==2){
        loadGrid(":/new/prefix1/Level two.txt");

    }
    else if (level==3){
        loadGrid(":/new/prefix1/Level three.txt");

    }
    else if (level > 3) {
        // QMessageBox::information(this, "Game Over", "Congratulations! You've completed the game.");
        // this->close();
        // clearGameObjects();
        // QApplication::quit();
        // return;
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,
                                         "You Win",
                                         "Congratulations! You've completed the game.",
                                         QMessageBox::Ok);

        if (reply == QMessageBox::Ok) {
            this->close();
            clearGameObjects();
            QApplication::quit();
        }
    }
    else {
        qDebug() << "Invalid level:" << level;
    }

}

void MainWindow::loadGrid(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file.";
        return;
    }

    QTextStream in(&file);
    int y = 0;
    int gridWidth = 0;
    int gridHeight = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList numbers = line.split(" ");
        gridWidth = numbers.size();

        for (int x = 0; x < numbers.size(); ++x) {
            int Type = numbers[x].toInt();
            QPixmap Image;

            switch (Type) {
            case 0:
                Image = QPixmap(":/new/prefix1/mr brown.png");  // Enemy
                break;
            case 1:
                Image = QPixmap(":/new/prefix1/grero land.png"); // Wood
                break;
            case 2:
                Image = QPixmap(":/new/prefix1/roro.png");    // Rock
                break;
            case 3:
                Image = QPixmap(":/new/prefix1/meaw.png");  // Meat (Coin)
                money++;
                break;
            case 4:
                Image = QPixmap(":/new/prefix1/cavoo.png");  // House
                break;
            case 5:
                Image = QPixmap(":/new/prefix1/552d013105f10942d289ce8dc0e8ff0e.png");  // Diamond
                break;
            default:
                Image = QPixmap("");
                break;
            }

            Image = Image.scaled(tileWidth, tileHeight);

            if (Type == 1) {
                WoodenBoxes *box = new WoodenBoxes();
                box->setPixmap(Image);
                box->setPos(x * tileWidth, y * tileHeight);
                scene->addItem(box);
            } else if (Type == 2) {
                RockBoxes *rock = new RockBoxes();
                rock->setPixmap(Image);
                rock->setPos(x * tileWidth, y * tileHeight);
                scene->addItem(rock);

            } else if (Type == 3) {
                coin *coins = new coin();
                coins->setPixmap(Image);
                coins->setPos(x * tileWidth, y * tileHeight);
                scene->addItem(coins);

            } else if (Type == 0) {  // Enemy
                Enemy *enemy = new Enemy();
                 enemy->setScenePointer(scene);
                enemy->setPixmap(Image);
                enemy->setPos(x * tileWidth, y * tileHeight);
                if (level==1)
                    enemy->speed=3;
                else if (level ==2)
                     enemy->speed=5;
                else if (level ==3)
                    enemy->speed=7;
                scene->addItem(enemy);

            }
            else if (Type == 4) {
               houseObject= new house();
                houseObject->setPixmap(Image);
                houseObject->setPos(x * tileWidth, y * tileHeight);
                houseObject->setZValue(100);
                scene->addItem(houseObject);


            }
            else if (Type == 5) {
                diamond= new Diamond();
                diamond->setPixmap(Image);
                diamond->setPos(x * tileWidth, y * tileHeight);
                diamond->setZValue(100);
                scene->addItem(diamond);
                diamonds++;


            }
            else {
                QGraphicsPixmapItem *Item = new QGraphicsPixmapItem(Image);
                Item->setPos(x * tileWidth, y * tileHeight);
                scene->addItem(Item);
            }
        }
        y++;
    }

    gridHeight = y;
    progressBar->setRange(0, money);
   // diamondBar->setRange(0,diamonds);
    scene->setSceneRect(0, 0, gridWidth * tileWidth, gridHeight * tileHeight);
}

void MainWindow::updateEnemyPosition() {
    if (!player) {
        qDebug()<<"Player is Null";
        qWarning() << "Player is null!";
        return;
    }
    for (QGraphicsItem* item : scene->items()) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(item)) {
            enemy->moveTowardsPlayer(player);
        }
    }
}

void MainWindow::updateProgressBar() {
    int coins = player->getCoins();
    progressBar->setValue(coins);
    if (coins == money && !hasWon) {
        hasWon = true;
    }
}
void MainWindow::updateDiamondBar(){
    int diamond=player->getDiamond();
    diamondBar->setValue(diamond);
}

void MainWindow::updatePlayerStats(int health, int diamonds)
{
    healthBar->setValue(health);
    diamondBar->setValue(diamonds);
}

void MainWindow::startNextLevel() {
    if (level > 3) {
        QMessageBox::information(this, "Game Over", "Congratulations! You've completed the game.");
        this->close();
        clearGameObjects();
        QApplication::quit();
        return;
    }

}


void MainWindow::restartGame() {
    progressBar->setValue(0);
    hasWon = false;
    progressBar->setEnabled(true);
    player->health=100;
    healthBar->setValue(100);
    healthBar->setEnabled(true);
    lost = false;


    for (QGraphicsItem* item : scene->items()) {
        if (dynamic_cast<Enemy*>(item)) {
            scene->removeItem(item);
            delete item;
        }
    }
    for (QGraphicsItem* item : scene->items()) {
        if (dynamic_cast<RockBoxes*>(item)) {
            scene->removeItem(item);
            delete item;
        }
    }

}
void MainWindow::startRockFallTimer() {
    QTimer *rockFallTimer = new QTimer(this);
    connect(rockFallTimer, &QTimer::timeout, this, &MainWindow::checkRocksForFalling);
    rockFallTimer->start(100);
}

void MainWindow::checkRocksForFalling() {
    qDebug() << "Checking rocks for falling...";

    if (!scene) {
        qDebug() << "Error: scene is null!";
        return;
    }

    for (QGraphicsItem* item : scene->items()) {
        if (RockBoxes* rock = dynamic_cast<RockBoxes*>(item)) {
            rock->fall();
        }
    }
}

void MainWindow::updateHealthBar() {

    healthBar->setValue(player->getHealth());
     if ( (player->getHealth() == 0))
        Lostfunc();


    if (player->getHealth() <= 50) {
        qDebug() << "Setting health bar to red...";
        healthBar->setStyleSheet("QProgressBar {"
                                 "border: 2px solid gray;"
                                 "border-radius: 5px;"
                                 "background-color: #2c2f38;"
                                 "text-align: center;}"
                                 "QProgressBar::chunk {"
                                 "background-color: red;"
                                 "border-radius: 3px;}");
    } else if (player->getHealth() <= 75) {
        qDebug() << "Setting health bar to orange...";
        healthBar->setStyleSheet("QProgressBar {"
                                 "border: 2px solid gray;"
                                 "border-radius: 5px;"
                                 "background-color: #2c2f38;"
                                 "text-align: center;}"
                                 "QProgressBar::chunk {"
                                 "background-color: orange;"
                                 "border-radius: 3px;}");
    } else {
        qDebug() << "Setting health bar to green...";
        healthBar->setStyleSheet("QProgressBar {"
                                 "border: 2px solid gray;"
                                 "border-radius: 5px;"
                                 "background-color: #2c2f38;"
                                 "text-align: center;}"
                                 "QProgressBar::chunk {"
                                 "background-color: blue;"
                                 "border-radius: 3px;}");
    }
}
void MainWindow::clearGameObjects() {
    for (QGraphicsItem* item : scene->items()) {

            scene->removeItem(item);
            delete item;
    }
}
void MainWindow::checkPlayerCollisions() {
    static bool transitionInProgress = false;

    if (hasWon&& !transitionInProgress) {
        qDebug() << "Collision happened";

        QList<QGraphicsItem*> collidingItems = player->collidingItems();


        for (QGraphicsItem* item : collidingItems) {
            if (item == houseObject) {
               qDebug() << "Player collided with house!";

                transitionInProgress = true;
               clearGameObjects();
                // if(hasWon){
                //     remainingTime=50;
                // }
              houseObject->checkCollisionwithPlayer(hasWon, level + 1);

               QTimer::singleShot(0, this, &MainWindow::close);

           qDebug() << "Collision";
             transitionInProgress = false;
                 hasWon=false;
                 break;
        }
    }
    }
}


int MainWindow::getLevel() {
    return level;
}

void MainWindow:: restartTimer(int time){
    remainingTime= time;
}

void MainWindow::updateCountdown() {

}
void MainWindow:: Lostfunc(){
    if (remainingTime <= 0 || (player->getHealth() == 0 && !lost)) {
            lost = true;
        qDebug()<<"Time&&&&"<<remainingTime;
        countdownTimer->stop();
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Game Over!");
        msgBox->setIconPixmap(QPixmap(":/new/prefix1/oops.png"));
        msgBox->setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
        msgBox->button(QMessageBox::Retry)->setText("Restart");
        msgBox->button(QMessageBox::Close)->setText("Exit");


        QMediaPlayer* p = new QMediaPlayer(this);
        QAudioOutput* audioOutput = new QAudioOutput(this);
        p->setAudioOutput(audioOutput);
        p->setSource(QUrl("qrc:/new/prefix1/you-loseheavy-echoed-voice-230555.mp3"));
        audioOutput->setVolume(50);
        p->play();

        int result=msgBox->exec();

        if (result == QMessageBox::Retry) {
            hide();
            restartGame();
            Loading* load = new Loading();
            load->show();
            qDebug() << "Restart button clicked!";
        } else if (result == QMessageBox::Close) {
            qDebug() << "Exit button clicked!";
            this->close();
            QApplication::quit();
        }
    }
}

void MainWindow::setPlayer(Player* player)
{
}

