#include "QWangSpeaker.h"


QWangSpeaker::QWangSpeaker(QObject *parent)
    : QObject{parent},
    sampleRate(16000),
    channelCount(1),
    sampleSize(16)
{}

QWangSpeaker::~QWangSpeaker()
{
    StopPlayer();
}

bool QWangSpeaker::StartPlayer(int sampleRate, int channelCount, int sampleSize)
{
    QAudioFormat qAudioFormat;
    qAudioFormat.setSampleRate(sampleRate);
    qAudioFormat.setChannelCount(channelCount);
    qAudioFormat.setSampleSize(sampleSize);
    qAudioFormat.setCodec("audio/pcm");
    qAudioFormat.setByteOrder(QAudioFormat::LittleEndian);
    qAudioFormat.setSampleType(QAudioFormat::SignedInt);

    out = new QAudioOutput(qAudioFormat,this);
    out->setVolume(0.5);
    if (!out) {
        return false;
    }

    audioIO = out->start();
    return true;
}

void QWangSpeaker::StopPlayer()
{
    if(out)
    out->stop();
}


qint64 QWangSpeaker::WritePlayer(QByteArray &audio_bytes){
    if(audioIO && !audio_bytes.isEmpty()){
        return audioIO->write((const char*)audio_bytes.data(),audio_bytes.size());
    }
    return 0;
}
