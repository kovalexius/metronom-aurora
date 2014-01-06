#ifndef PULSESIMPLE_H
#define PULSESIMPLE_H

// wraps the pulse-simple library
// for playing simple wav files

#include <QFile>
#include <QDebug>
#include <pulse/simple.h>
#include <pulse/error.h>

class WavFile {
public:
    WavFile() {
    }

    bool load(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open wav file " << filename;
            return false;
        }

        char header[44];
        if (file.read(header, 44) != 44) {
            qDebug() << "Failed to read from wav file " << filename;
            return false;
        }

        unsigned short audioFormat;
        unsigned short numChannels;
        unsigned int sampleRate;
        unsigned int byteRate;
        unsigned short blockAlign;
        unsigned short bitsPerSample;
        audioFormat = *(unsigned short*)(header + 20);
        numChannels = *(unsigned short*)(header + 22);
        sampleRate = *(unsigned int*)(header + 24);
        byteRate = *(unsigned int*)(header + 28);
        blockAlign = *(unsigned short*)(header + 32);
        bitsPerSample = *(unsigned short*)(header + 34);

        qDebug() << "Loaded " << filename << " "
                 << "Audio format: " << audioFormat << " "
                 << "Num channels: " << numChannels << " "
                 << "Sample rate: " << sampleRate << " "
                 << "Byte rate: " << byteRate << " "
                 << "Block align: " << blockAlign << " "
                 << "Bits per sample: " << bitsPerSample;

        switch (bitsPerSample) {
        case 8: spec.format = PA_SAMPLE_U8; break;
        case 16: spec.format = PA_SAMPLE_S16LE; break;
        case 24: spec.format = PA_SAMPLE_S24LE; break;
        }
        spec.rate = sampleRate;
        spec.channels = numChannels;

        rawData = file.readAll();

        return true;
    }

    pa_sample_spec spec;
    QByteArray rawData;
};

class PulseSimple
{
public:
    PulseSimple() {

    }

    ~PulseSimple() {
        int error;
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
