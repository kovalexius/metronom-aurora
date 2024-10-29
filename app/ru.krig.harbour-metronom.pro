# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = ru.krig.harbour-metronom

QT += multimedia

CONFIG += sailfishapp \
        link_pkgconfig \
        auroraapp \
        pulse \

SOURCES += src/harbour-metronom.cpp \
    src/audioplayer.cpp \
    src/timedisplay.cpp

data.files = data
data.path = $${DEPLOYMENT_PATH}

INCLUDEPATH += /usr/include/resource/qt5

PKGCONFIG += sailfishapp \
    libresourceqt5 \

OTHER_FILES += qml/harbour-metronom.qml \
    qml/cover/CoverPage.qml \
    ru.krig.harbour-metronom.desktop \
    qml/pages/Settings.qml \
    qml/pages/Metronome.qml \
    data/fine2.wav \
    data/fine1.wav \
    data/high.wav \
    data/low.wav \

INSTALLS += data

HEADERS += \
    src/audioplayer.h \
    src/timedisplay.h \
    src/PulseSimple.h \
    src/WavFile.h

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172
