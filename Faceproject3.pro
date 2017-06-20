#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T20:18:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Faceproject3
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
        camaraget.cpp

HEADERS  += camaraget.h

FORMS    += camaraget.ui

INCLUDEPATH += /usr/local/include/opencv  /usr/local/include/opencv2  usr/local/include   /usr/include/python2.7
#INCLUDEPATH += "/usr/local/include"

LIBS += /usr/local/lib/libopencv_highgui.so \
      /usr/local/lib/libopencv_core.so \
         /usr/local/lib/libopencv_features2d.so      \
 /usr/local/lib/libopencv_flann.so     \
 /usr/local/lib/libopencv_imgcodecs.so     \
 /usr/local/lib/libopencv_imgproc.so        \
 /usr/local/lib/libopencv_ml.so    \
 /usr/local/lib/libopencv_objdetect.so    \
 /usr/local/lib/libopencv_photo.so    \
/usr/local/lib/libopencv_shape.so  \
/usr/local/lib/libopencv_stitching.so \
/usr/local/lib/libopencv_superres.so \
/usr/local/lib/libopencv_video.so  \
/usr/local/lib/libopencv_videoio.so \
/usr/local/lib/libopencv_videostab.so \
#/usr/lib/x86_64-linux-gnu/libpython2.7.a
#/usr/lib/python2.7/config-x86_64-linux-gnu/libpython2.7.a
/usr/lib/python2.7/config-x86_64-linux-gnu/libpython2.7.so

DISTFILES += \
    Face_Cut.xml

RESOURCES += \
    meihua.qrc
