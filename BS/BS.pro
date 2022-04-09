QT       += core gui multimedia serialport multimediawidgets


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

TARGET_ARCH = $${QT_ARCH}
contains(TARGET_ARCH, arm){
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    INCLUDEPATH += /opt/fsl-imx-x11/4.1.15-2.1.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include
} else {
    LIBS += -L/usr/local/lib \
            -lopencv_core \
            -lopencv_highgui \
            -lopencv_imgproc \
            -lopencv_videoio \
            -lopencv_imgcodecs

    #INCLUDEPATH可写可不写，系统会到找到此路径
    INCLUDEPATH += /usr/local/include
}

SOURCES += \
    bjwindow.cpp \
    camera.cpp \
    cwwindow.cpp \
    games/coinchoice.cpp \
    games/coingame.cpp \
    games/dataconfig.cpp \
    games/gamewindow.cpp \
    games/mycoin.cpp \
    games/playsence.cpp \
    lifewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    musicwindow.cpp \
    mybutton.cpp \
    pictureW/picturewindow.cpp \
    videowindow.cpp

HEADERS += \
    bjwindow.h \
    camera.h \
    cwwindow.h \
    games/coinchoice.h \
    games/coingame.h \
    games/dataconfig.h \
    games/gamewindow.h \
    games/mycoin.h \
    games/playsence.h \
    lifewindow.h \
    mainwindow.h \
    musicwindow.h \
    mybutton.h \
    pictureW/picturewindow.h \
    videowindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc