QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    faceconfirm.cpp \
    main.cpp \
    server.cpp

HEADERS += \
    faceconfirm.h \
    server.h

LIBS += D:\Course\opencv452\x64\mingw\lib\libopencv*
LIBS += D:\Course\SeetaFace\lib\libSeeta*
INCLUDEPATH += D:\Course\opencv452\include
INCLUDEPATH += D:\Course\opencv452\include\opencv2
INCLUDEPATH += D:\Course\SeetaFace\include
INCLUDEPATH += D:\Course\SeetaFace\include\seeta

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
