#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

#define USE_RESOURCE 1
#define USE_AUDIORESOURCE 0
#define USE_QSOUNDEFFECT 1
#define USE_PULSEAUDIO 0

#if USE_RESOURCE
#include <policy/resource-set.h>
#endif

#if USE_AUDIORESOURCE
#include <audioresource.h>
#endif

#if USE_QSOUNDEFFECT
#include <QtMultimedia>
#include <QSoundEffect>
#endif

#if USE_PULSEAUDIO
#include "PulseSimple.h"
#endif

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = 0);
    ~AudioPlayer();

signals:

public slots:
    void playClick(int bar, int measure, int soundId);

#if USE_RESOURCE
private slots:
    void resourceAcquiredHandler(const QList<ResourcePolicy::ResourceType>&);
    void resourceLostHandler();

private:
    ResourcePolicy::ResourceSet *m_resourceSet;
    ResourcePolicy::AudioResource *m_audioResource;
#endif

private:
#if USE_QSOUNDEFFECT
    QSoundEffect sounds[4];
#endif
#if USE_PULSEAUDIO
    WavFile wavs[4];
    PulseSimple pulse;
#endif
};

#endif // AUDIOPLAYER_H
