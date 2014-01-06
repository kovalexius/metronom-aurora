#ifndef TIMEDISPLAY_H
#define TIMEDISPLAY_H

#include <QObject>

class TimeDisplay : public QObject
{
    Q_OBJECT
public:
    explicit TimeDisplay(QObject *parent = 0);

signals:

public slots:

};

#endif // TIMEDISPLAY_H
