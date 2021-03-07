TEMPLATE = app TARGET = pmt

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

MOC_DIR     = build/moc
OBJECTS_DIR = build/obj
UI_DIR      = build/ui
RCC_DIR     = build/

SOURCES += \
    PAWrapper.cpp \
    WindowManager.cpp \
    main.cpp

HEADERS += \
    IOBase.h \
    PAWrapper.h \
    WindowManager.h

unix: LIBS += -L$$PWD/../portaudio/lib/.libs/ -lportaudio
linux-g++*: LIBS += -lrt -lm -lasound -pthread
macx: LIBS += -framework CoreServices -framework CoreFoundation -framework AudioUnit -framework AudioToolbox -framework CoreAudio

INCLUDEPATH += $$PWD/../portaudio/include
DEPENDPATH += $$PWD/../portaudio/include
