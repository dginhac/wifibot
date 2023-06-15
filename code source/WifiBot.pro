QT += core gui
QT += network
QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#INCLUDEPATH += C:\Qt\Tools\QtDesignStudio\qt6_design_studio_reduced_version\qml\QtWebEngine

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    myrobot.cpp

HEADERS += \
    camera.h \
    controllerType.h \
    direction.h \
    mainwindow.h \
    myrobot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
