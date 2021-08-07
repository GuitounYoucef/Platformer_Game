QT       += core gui
QT += multimedia multimediawidgets
QT += qml quick






greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backgroundimage.cpp \
    briks.cpp \
    bullet.cpp \
    castle.cpp \
    cloud.cpp \
    coin.cpp \
    endstage.cpp \
    enemy.cpp \
    goomba.cpp \
    inanimateobject.cpp \
    koopa.cpp \
    lake.cpp \
    main.cpp \
    mushroom.cpp \
    myscene.cpp \
    pipe.cpp \
    piranha.cpp \
    platform.cpp \
    player.cpp \
    questbox.cpp \
    spiny.cpp \
    tree.cpp \
    walkers.cpp \
    water.cpp \
    widget.cpp

HEADERS += \
    backgroundimage.h \
    briks.h \
    bullet.h \
    castle.h \
    cloud.h \
    coin.h \
    endstage.h \
    enemy.h \
    goomba.h \
    inanimateobject.h \
    koopa.h \
    lake.h \
    mushroom.h \
    myscene.h \
    pipe.h \
    piranha.h \
    platform.h \
    player.h \
    questbox.h \
    spiny.h \
    tree.h \
    walkers.h \
    water.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    QML.qrc \
    images.qrc \
    maps/maps.qrc \
    sound.qrc

DISTFILES += \
    QML/water.qml
