#ifndef WAVFILE_H
#define WAVFILE_H

#include <QFile>
#include <QDebug>

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

#endif // WAVFILE_H
