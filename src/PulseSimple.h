#ifndef PULSESIMPLE_H
#define PULSESIMPLE_H

// wraps the pulse-simple library
// for playing simple wav files

#include <pulse/simple.h>
#include <pulse/error.h>
#include "WavFile.h"

class PulseSimple
{
public:
    PulseSimple() {

    }

    ~PulseSimple() {
        //int error;
        if (s) {
            //if (pa_simple_drain(s, &error) < 0)
            //        qDebug() << "Error when draining stream: " << pa_strerror(error);
            pa_simple_free(s);
        }
    }

    bool createStream(WavFile* wav) {
        int error;
        pa_buffer_attr attr;
        attr.maxlength = 1024;
        attr.tlength = 2048;
        attr.prebuf = 0;
        attr.minreq = 512;
        qDebug() << "Creating stream...";
        s = pa_simple_new(NULL, "Metronom", PA_STREAM_PLAYBACK, NULL, "Metronom", &wav->spec, NULL, &attr, &error);
        if (!s) {
            qDebug() << "Error when creating stream: " << pa_strerror(error);
        }
        qDebug() << "Stream created.";
        return true;
    }

    void play(WavFile* wav) {
        int error;
        //if (pa_simple_drain(s, &error) < 0) {
        //    qDebug() << "Error when draining stream: " << pa_strerror(error);
        //}
        qDebug() << "Writing data to stream";
        if (pa_simple_write(s, wav->rawData.data(), wav->rawData.size(), &error) < 0) {
            qDebug() << "Error when playing sample: " << pa_strerror(error);
        }
        qDebug() << "Write completed";
    }

private:
    pa_simple *s;
};

#endif // PULSESIMPLE_H
