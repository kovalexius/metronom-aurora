#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QSoundEffect>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = 0);

signals:

public slots:
    void playClick(int bar, int measure, int soundId);

private:
    QSoundEffect sounds[4];
};

#endif // AUDIOPLAYER_H
