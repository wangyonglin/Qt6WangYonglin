#ifndef QWANGSPEAKER_H
#define QWANGSPEAKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QFile>

#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>
#include <QAudioFormat>
#include <QAudioInput>
#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include <QVector>
#include <QDataStream>
#include <QObject>

class QWangSpeaker : public QObject
{
    Q_OBJECT
public:
    explicit QWangSpeaker(QObject *parent = nullptr);
    ~QWangSpeaker();
    bool StartPlayer(int sampleRate=16000,
                     int channelCount=1,
                     int sampleSize=16);
    void StopPlayer();
    qint64 WritePlayer(QByteArray &audio_bytes);

private:

    QAudioOutput *out;
    QIODevice *audioIO;
    QTimer *audioPlayTimer;
    QThread *timerTHread;
    int sampleRate=16000;
    int channelCount=1;
    int sampleSize=16;

};

#endif // QWANGSPEAKER_H
