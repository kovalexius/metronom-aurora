# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = harbour-metronom

QT += multimedia

CONFIG += sailfishapp

DEPLOYMENT_PATH = /usr/share/$${TARGET}

SOURCES += src/harbour-metronom.cpp \
    audioplayer.cpp \
    timedisplay.cpp

data.files = data
data.path = $${DEPLOYMENT_PATH}

OTHER_FILES += qml/harbour-metronom.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-metronom.spec \
    harbour-metronom.desktop \
    qml/pages/Settings.qml \
    qml/pages/Metronome.qml \
    data/fine2.wav \
    data/fine1.wav \
    data/high.wav \
    data/low.wav

INSTALLS += data

HEADERS += \
    audioplayer.h \
    timedisplay.h
