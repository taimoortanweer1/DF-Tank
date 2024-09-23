QT       += core gui
QT += network
QMAKE_CFLAGS += -Wa,-mbig-obj
QMAKE_CXXFLAGS += -Wa,-mbig-obj
QT += charts
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Comunication.cpp \
    DoWork.cpp \
    main.cpp \
    df_tank_v1.cpp \
    qcustomplot.cpp

HEADERS += \
    Comunication.h \
    DoWork.h \
    df_tank_v1.h \
    qcustomplot.h


FORMS += \
    df_tank_v1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    button_icons.qrc
