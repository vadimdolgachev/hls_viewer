QT       += core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    VarianStreamWidgetItem.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    VarianStreamWidgetItem.h

FORMS += \
    MainWindow.ui \
    VarianStreamWidgetItem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


unix:!macx: LIBS += -L$$OUT_PWD/../hls_lib/ -lhls_lib

INCLUDEPATH += $$PWD/../hls_lib
DEPENDPATH += $$PWD/../hls_lib

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../hls_lib/libhls_lib.a