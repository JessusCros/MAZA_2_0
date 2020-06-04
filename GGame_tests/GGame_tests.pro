QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameunit.cpp \
    main.cpp

HEADERS += \
    gameunit.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    C:/Users/Александр Косенков/Desktop/Floors/tile001.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile002.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile002.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile003.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile004.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile005.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile006.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile007.png \
    C:/Users/Александр Косенков/Desktop/Floors/tile008.png \
    C:/Users/Александр Косенков/Desktop/UpWalls/tile065.png \
    C:/Users/Александр Косенков/Desktop/ezgif-6-341d506745ec-png-68x68-sprite-png.zip

RESOURCES += \
    Image.qrc
