#include "audioplayer.h"

#include <QDebug>

#include <sailfishapp.h>

namespace {
    bool allow_sound = false;

#if USE_AUDIORESOURCE
    audioresource_t *resource = NULL;

    void on_acquired(audioresource_t *audio_resource, bool acquired, void *user_data)
    {
        if (acquired) {
            allow_sound = true;
        } else {
            allow_sound = false;
        }
    }
#endif
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

#if USE_AUDIORESOURCE
    resource = audioresource_init(AUDIO_RESOURCE_MEDIA, on_acquired, user_data);
    audioresource_acquire(resource);

    for (size_t i = 0; i < sizeof(files) / sizeof(const char*); ++i) {
        qDebug() << "Sounds:" << SailfishApp::pathTo(files[i]).toLocalFile();
        sounds[i].setSource(SailfishApp::pathTo(files[i]));
    }
#endif

}

AudioPlayer::~AudioPlayer() {
#if USE_AUDIORESOURCE
    audioresource_release(resource);
    audioresource_free(resource);
    resource = NULL;
#endif
}

void AudioPlayer::playClick(int bar, int measure, int soundId) {
    if (allow_sound) {
#if USE_AUDIORESOURCE
        int n = (bar == 1) ? 0 : 1;
        if (measure == 7 && bar == 5)
            n = 0;
        if (sounds[soundId*2 + n].status() == QSoundEffect::Ready)
            sounds[soundId*2 + n].play();
#endif
    }
}
