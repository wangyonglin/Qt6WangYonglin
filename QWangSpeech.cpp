#include "QWangSpeech.h"

QWangSpeech::QWangSpeech(QObject *parent)
    : QWangThreader{parent},
      sampleRate(16000),
      channelCount(1),
      sampleSize(16)
{

}

QWangSpeech::~QWangSpeech()
{

}


bool QWangSpeech::StartPlayer(int sampleRate,
                              int channelCount,
                              int sampleSize)
{
    QAudioFormat format;
    format.setSampleRate(sampleRate);
    format.setChannelCount(channelCount);      // 设定声道数目，mono(平声道)的声道数目是1；stero(立体声)的声道数目是2
    format.setSampleSize(sampleSize);       // 采样位深
    format.setCodec("audio/pcm");   // 设置唯一支持的codec
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }
    audioInput = new QAudioInput(format,this);
    audioInput->setVolume(0.5);
    qIODevice = audioInput->start();
    if (qIODevice) {
        qDebug() << "device available";
        loopStart();
        return true;
    }
    return false;
}


void QWangSpeech::loopRunnable()
{
    if(isRunning() && qIODevice){
        QByteArray audio_bytes= qIODevice->readAll();
        if(!audio_bytes.isEmpty()){
            emit onRefreshFrame(audio_bytes);
        }
    }
}


void QWangSpeech::StopPlayer()
{
    loopStop();
    qIODevice->close();
    qIODevice=nullptr;
    audioInput->stop();
    loopStop();
}


