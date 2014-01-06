#include "audioplayer.h"

#include <QDebug>
#include <QSoundEffect>

#include <sailfishapp.h>
#include <audioresource.h>

namespace {
    bool allow_sound = false;
    audioresource_t *resource = NULL;

    void on_acquired(audioresource_t *audio_resource, bool acquired, void *user_data)
    {
        if (acquired) {
            allow_sound = true;
        } else {
            allow_sound = false;
        }
    }
}

AudioPlayer::AudioPlayer(QObject *parent) :
    QObject(parent)
{
    const char* files [] = {
        "data/fine1.wav",
        "data/fine2.wav",
        "data/high.wav",
        "data/low.wav"
    };

    // Use game because we're low latency. This classification is ...eh.
    resource = audioresource_init(AUDIO_RESOURCE_GAME, on_acquired, user_data);

    for (size_t i = 0; i < sizeof(files) / sizeof(const char*); ++i) {
        sounds[i].setSource(SailfishApp::pathTo(files[i]));
    }

    audioresource_acquire(resource);
}

AudioPlayer::~AudioPlayer() {
    audioresource_release(resource);
    audioresource_free(resource);
    resource = NULL;
}

void AudioPlayer::playClick(int bar, int measure, int soundId) {
    qDebug() << bar << measure << soundId;
    int n = (bar == 1) ? 0 : 1;
    if (measure == 7 && bar == 5)
        n = 0;
    if (sounds[soundId*2 + n].status() == QSoundEffect::Ready)
        sounds[soundId*2 + n].play();
}
