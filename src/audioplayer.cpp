#include "audioplayer.h"

#include <QDebug>

#include <sailfishapp.h>

#if USE_RESOURCE
#include <QtCore/QCoreApplication>
#endif

#include "PulseSimple.h"

namespace {

#if USE_AUDIORESOURCE
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
#elif USE_RESOURCE
    bool allow_sound = false;
#else
    bool allow_sound = true;
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
    resource = audioresource_init(AUDIO_RESOURCE_MEDIA, on_acquired, NULL);
    audioresource_acquire(resource);
#endif

#if USE_QSOUNDEFFECT
    for (size_t i = 0; i < sizeof(files) / sizeof(const char*); ++i) {
        qDebug() << "Sounds:" << SailfishApp::pathTo(files[i]).toLocalFile();
        sounds[i].setSource(SailfishApp::pathTo(files[i]));
    }
#endif

#if USE_RESOURCE
    // Resource management stuff
    m_resourceSet = new ResourcePolicy::ResourceSet(QLatin1String("player"), 0, false, true);
    m_audioResource = new ResourcePolicy::AudioResource(QLatin1String("player"));
    m_audioResource->setProcessID(QCoreApplication::applicationPid());
    m_audioResource->setStreamTag(QLatin1String("media.name"), QLatin1String("*"));
    m_audioResource->setOptional(false);
    m_resourceSet->addResourceObject(m_audioResource);
    connect(m_resourceSet, SIGNAL(resourcesGranted(QList<ResourcePolicy::ResourceType>)), this, SLOT(resourceAcquiredHandler(QList<ResourcePolicy::ResourceType>)));
    connect(m_resourceSet, SIGNAL(lostResources()), this, SLOT(resourceLostHandler()));
    QCoreApplication::instance()->installEventFilter(this);
    m_resourceSet->acquire();
#endif

#if USE_PULSEAUDIO
    for (size_t i = 0; i < sizeof(files) / sizeof(const char*); ++i) {
        QUrl f = SailfishApp::pathTo(files[i]);
        wavs[i].load(f.toLocalFile());
    }
    pulse.createStream(&wavs[0]);
#endif

}

AudioPlayer::~AudioPlayer() {
#if USE_RESOURCE
    m_resourceSet->release();
#endif
#if USE_AUDIORESOURCE
    audioresource_release(resource);
    audioresource_free(resource);
    resource = NULL;
#endif
}

#if USE_RESOURCE
void AudioPlayer::resourceAcquiredHandler(const QList<ResourcePolicy::ResourceType>&) {
    allow_sound = true;
    qDebug() << "Resource acquired";
}
void AudioPlayer::resourceLostHandler() {
    allow_sound = false;
    qDebug() << "Resource lost";
}
#endif

void AudioPlayer::playClick(int bar, int measure, int soundId) {
    qDebug() << "playClick " << bar << measure << soundId;
    if (allow_sound) {
        int n = (bar == 1) ? 0 : 1;
        if (measure == 7 && bar == 5)
            n = 0;
        int playidx = soundId*2 + n;

#if USE_QSOUNDEFFECT
        if (sounds[playidx].status() == QSoundEffect::Ready)
            sounds[playidx].play();
#endif
#if USE_PULSEAUDIO
        pulse.play(&wavs[playidx]);
#endif
    }
}
