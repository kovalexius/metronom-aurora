#include "audioplayer.h"

#include <QDebug>
#include <QSoundEffect>

#include <sailfishapp.h>

AudioPlayer::AudioPlayer(QObject *parent) :
    QObject(parent)
{
    const char* files [] = {
        "data/fine1.wav",
        "data/fine2.wav",
        "data/high.wav",
        "data/low.wav"
    };
    for (size_t i = 0; i < sizeof(files) / sizeof(const char*); ++i) {
        sounds[i].setSource(SailfishApp::pathTo(files[i]));
    }
}

void AudioPlayer::playClick(int bar, int measure, int soundId) {
    qDebug() << bar << measure << soundId;
    int n = (bar == 1) ? 0 : 1;
    if (measure == 7 && bar == 5)
        n = 0;
    if (sounds[soundId*2 + n].status() == QSoundEffect::Ready)
        sounds[soundId*2 + n].play();
}
