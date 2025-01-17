#include "loading.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>

 QMediaPlayer* globalBackgroundMusicPlayer = nullptr;
  QAudioOutput* globalAudioOutput = nullptr;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    // QAudioOutput* mu = new QAudioOutput();
    // mu ->setVolume(50);
    // QMediaPlayer * music = new QMediaPlayer();
    // music ->setAudioOutput(mu);
    // music->setSource(QUrl(":/new/prefix1/start.mp3"));
    // music->play();
    globalBackgroundMusicPlayer = new QMediaPlayer();
    globalAudioOutput = new QAudioOutput();
    globalBackgroundMusicPlayer->setAudioOutput(globalAudioOutput);
    globalBackgroundMusicPlayer->setSource(QUrl("qrc:/new/prefix1/8-bit-background-music-for-arcade-game-come-on-mario-164702.mp3"));
    globalAudioOutput->setVolume(0.1);
    globalBackgroundMusicPlayer->play();

    // MainWindow w(nullptr, 1);
    // w.show();
    Loading l;
    l.show();





    return a.exec();
}
