TEMPLATE = app TARGET = pmt

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

MOC_DIR     = build/moc
OBJECTS_DIR = build/obj
UI_DIR      = build/ui
RCC_DIR     = build/

SOURCES += \
    main.cpp \
    pawrapper.cpp

HEADERS += \
    iobase.h \
    pawrapper.h

INCLUDEPATH += $$PWD/../portaudio/lib/.libs $$PWD/../portaudio/include

macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../portaudio/lib/.libs/ -lportaudio -framework CoreServices -framework CoreFoundation -framework AudioUnit -framework AudioToolbox -framework CoreAudio
else:linux-g++*: LIBS += -L$$PWD/../portaudio/lib/.libs/ -lportaudio -lrt -lm -lasound -pthread
