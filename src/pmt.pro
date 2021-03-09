TEMPLATE = app TARGET = pmt

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

MOC_DIR     = build/moc
OBJECTS_DIR = build/obj
UI_DIR      = build/ui
RCC_DIR     = build/

SOURCES += \
    AudioIO.cpp \
    WindowManager.cpp \
    PAWrapper.cpp \
    main.cpp

HEADERS += \
    AudioIO.h \
    AudioIOVariant.h \
    AudioIOVariantFactory.h \
    PAWrapper.h \
    WindowManager.h

unix: LIBS += -L$$PWD/../portaudio/lib/.libs/ -L$$PWD/../aubio/build/src/ -lportaudio -laubio
linux-g++*: LIBS += -lrt -lm -lasound -pthread
macx: LIBS += -framework CoreServices -framework CoreFoundation -framework AudioUnit -framework AudioToolbox -framework CoreAudio

INCLUDEPATH += $$PWD/../portaudio/include $$PWD/../aubio/src
DEPENDPATH += $$PWD/../portaudio/include $$PWD/../aubio/src
