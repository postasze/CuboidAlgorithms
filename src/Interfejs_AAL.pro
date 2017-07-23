#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T13:23:59
#
#-------------------------------------------------

QT       += core gui
QT       += charts
QT       += qml quick
QT       += widgets quickwidgets

CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interfejs_AAL
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    manualdatainsertform.cpp \
    randomdatainsertform.cpp \
    dataimportfromfileform.cpp \
    algorithmform.cpp \
    displayinputdataform.cpp \
    graphdisplayform.cpp \
    cuboidsdisplayform.cpp \
    cuboids.cpp \
    dataobject.cpp

HEADERS  += mainwindow.h \
    manualdatainsertform.h \
    randomdatainsertform.h \
    dataimportfromfileform.h \
    algorithmform.h \
    displayinputdataform.h \
    graphdisplayform.h \
    cuboidsdisplayform.h \
    cuboids.h \
    dataobject.h

FORMS    += mainwindow.ui \
    manualdatainsertform.ui \
    randomdatainsertform.ui \
    dataimportfromfileform.ui \
    algorithmform.ui \
    displayinputdataform.ui \
    graphdisplayform.ui \
    cuboidsdisplayform.ui

DISTFILES += \
    prostopadlosciany4 \
    prostopadlosciany3.txt \
    prostopadlosciany2.txt \
    prostopadlosciany1.txt \
    prostopadlosciany.txt

RESOURCES += \
    chapter2-methods.qrc

DESTPATH = /home/pawel/Pulpit/programy/programy_Qt/Interfejs_AAL
target.path = $$DESTPATH

qml.files = *.qml
qml.path = $$DESTPATH

INSTALLS += target qml
