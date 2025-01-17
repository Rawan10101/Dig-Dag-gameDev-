#include "loading.h"
#include "ui_loading.h"
#include "mainwindow.h"
#include<QAudioOutput>
#include<QMediaPlayer>

Loading::Loading(QWidget *parent)
    : QDialog(parent)
    , progressValue(0),
    ui(new Ui::Loading)
{
     ui->setupUi(this);
    QString styleSheet = R"(
    QDialog {
        background-image: url(":/new/prefix1/welcome adv.jpg");
        background-position: center;
        background-repeat: no-repeat;
        background-attachment: fixed;
    }
    )";
    ui->progressBar->hide();
    this->setStyleSheet(styleSheet);

    ui->progressBar->setValue(progressValue);
    ui->progressBar->setRange(0, 100);

    ui-> progressBar->setStyleSheet("QProgressBar {"
                                   "border: 2px solid gray;"
                                   "border-radius: 5px;"
                                   "background-color: #2c2f38;"
                                   "text-align: center;"
                                   "}"
                                   "QProgressBar::chunk {"
                                   "background-color: rgba(101, 67, 33, 255);"
                                   "border-radius: 3px;"
                                   "}");


}
void Loading::updateProgress()
{
    if (progressValue < 100) {
        progressValue += 1;
        ui->progressBar->setValue(progressValue);
    } else {
        timer->stop();
        hide();
        MainWindow* mainw=new MainWindow(nullptr, 1);
       // mainw->loadGrid(":/new/prefix1/Level one.txt");
        mainw->show();
    }
}
Loading::~Loading()
{
    delete ui;
}

void Loading::on_pushButton_clicked()
{
    ui->progressBar->show();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Loading::updateProgress);
    timer->start(100);

}

QString bold(const QString &text) {
    return QString("<b>%1</b>").arg(text);  //if wanted to bold the text to be clearer
}
void Loading::on_pushButton_2_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: #f8f1e4;" // Light beige background
        "}"
        "QLabel {"
        "    color: black;" // Dark red text
        "    font-weight: bold;" // Optional: make it bold
        "}"
        "QPushButton {"
        "    background-color: #5b85aa;" // Blue buttons
        "    color: white;"
        "    border-radius: 4px;"
        "    padding: 5px;"
        "}"
        );

    msgBox.setWindowTitle("Game Rules");
    msgBox.setText("Welcome to the Adventure Game! Your goal is to survive and progress through three challenging levels. Here's how to play \n"
                    "Objective: \n"
                   "1. Collect all the meat scattered on the grid.\n"
                   "2. Once all meat are collected, the house will open, allowing you to progress to the next level.\n"
                   "How to Play:\n"
                   "1. Avoid enemies and rocks.\n"
                   "2. Move away from enemies to avoid losing.\n"
                   "3. Be careful not to collide with rocks.\n"
                   "4. Use strategic movement to collect all the meat while dodging obstacles.\n"
                   "5. You can pause the game when you want.\n"
                   "6. You can upgrade your health and your speed from the shop.\n"
                   "Progress through levels:\n"
                   "1. Enemy Speed: Increases with each level.\n"
                   "2. Number of meat: More meat are added in higher levels.\n"
                   "3. Grid Complexity: The layout becomes trickier, with more obstacles and tighter paths.\n"
                   "Pro Tip: "
                   "Plan your moves carefully to avoid enemies and obstacles while collecting meat. "
                   "Use open spaces to your advantage for a quick escape if needed.\n"
                   "Click OK to start your journey. Good luck!\n");


    // msgBox.setStyleSheet(
    //     "QMessageBox {"
    //     "    background-image: url(:/new/prefix1/Screenshot 2024-11-25 180319.png);"
    //     "    background-position: center;"
    //     "    background-repeat: no-repeat;"
    //     "    border: 2px solid gray;"
    //     "    border-radius: 10px;"
    //     "    padding: 10px;"
    //     "}"
    //     );
    msgBox.exec();
}

