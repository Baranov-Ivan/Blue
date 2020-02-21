QT       += core gui
QT       += network

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
    Model/dijkstrasalg.cpp \
    Model/edge.cpp \
    Model/gamelogic.cpp \
    Model/node.cpp \
    Model/socketservice.cpp \
    Model/sockettest.cpp \
    Model/starter.cpp \
    Model/strategy.cpp \
    Model/structs.cpp \
    Model/train.cpp \
    Presenter/createmultiplayerpresenter.cpp \
    Presenter/enterexistinggamepresenter.cpp \
    Presenter/mainwindowchangingpresenter.cpp \
    Presenter/singleplayerpresenter.cpp \
    View/askselect.cpp \
    View/mainwindow.cpp \
    View/mainwindowforcreatemultigame.cpp \
    View/mainwindowforenterexistinggame.cpp \
    View/mainwindowforsingleplay.cpp \
    Render/graphwidget.cpp \
    main.cpp \
    Render/statshandler.cpp \
    Render/statslabel.cpp

HEADERS += \
    Model/Collections.h \
    Model/Collections.h \
    Model/dijkstrasalg.h \
    Model/edge.h \
    Model/gamelogic.h \
    Model/isocketservice.h \
    Model/istarter.h \
    Model/node.h \
    Model/socketservice.h \
    Model/sockettest.h \
    Model/starter.h \
    Model/strategy.h \
    Model/structs.h \
    Model/train.h \
    Presenter/createmultiplayerpresenter.h \
    Presenter/enterexistinggamepresenter.h \
    Presenter/mainwindowchangingpresenter.h \
    Presenter/singleplayerpresenter.h \
    View/askselect.h \
    View/mainwindow.h \
    View/mainwindowforcreatemultigame.h \
    View/mainwindowforenterexistinggame.h \
    View/mainwindowforsingleplay.h \
    Render/graphwidget.h \
    Render/statshandler.h \
    Render/statslabel.h

FORMS += \
    View/askselect.ui \
    View/mainwindowforcreatemultigame.ui \
    View/mainwindowforenterexistinggame.ui \
    View/mainwindowforsingleplay.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
