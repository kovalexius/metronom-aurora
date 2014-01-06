#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

#define USE_AUDIORESOURCE 0

#if USE_AUDIORESOURCE
#include <QtMultimedia>
#include <QSoundEffect>
#include <audioresource.h>
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

private:
#if USE_AUDIORESOURCE
    QSoundEffect sounds[4];
#endif
};

#endif // AUDIOPLAYER_H
