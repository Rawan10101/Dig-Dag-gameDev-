
QT       += core gui
QT +=multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coin.cpp \
    diamond.cpp \
    dig-dag/build/shoopingwindow.cpp \
    dig-dag/shopping.cpp \
    enemy.cpp \
    health.cpp \
    house.cpp \
    loading.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    player.cpp \
    rockboxes.cpp \
    woodenboxes.cpp

HEADERS += \
    coin.h \
    diamond.h \
    dig-dag/build/shoopingwindow.h \
    dig-dag/shopping.h \
    enemy.h \
    globals.h \
    health.h \
    house.h \
    loading.h \
    mainwindow.h \
    map.h \
    player.h \
    rockboxes.h \
    woodenboxes.h

FORMS += \
    dig-dag/build/shoopingwindow.ui \
    loading.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc \
    Resources.qrc \
    build/Resources.qrc \
    level.qrc

DISTFILES += \
    ../../../Downloads/animated ene.jpg \
    ../adv start.mp3
