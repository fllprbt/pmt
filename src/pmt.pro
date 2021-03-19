TEMPLATE = app TARGET = pmt

QT = core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

MOC_DIR     = build/moc
OBJECTS_DIR = build/obj
UI_DIR      = build/ui
RCC_DIR     = build/

SOURCES += \
    AubioWrapper.cpp \
    AudioIO.cpp \
    PitchUtils.cpp \
    WindowManager.cpp \
    PAWrapper.cpp \
    main.cpp

HEADERS += \
    AubioWrapper.h \
    AudioIO.h \
    AudioIOVariant.h \
    AudioIOVariantFactory.h \
    PAWrapper.h \
    PitchUtils.h \
    Types.h \
    WindowManager.h

linux-g++*: LIBS += -lrt -lm -lasound -pthread -lportaudio -laubio
