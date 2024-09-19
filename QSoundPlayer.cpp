#include "QSoundPlayer.h"
#include <QDebug>
#include <QAudioSink>

Qt6WangYonglin::QSoundPlayer::QSoundPlayer(QObject *parent)
    : QObject{parent}
{
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::UInt8);
    qMediaDevices=new QMediaDevices(this);
    qlistAudioDevice= qMediaDevices->audioOutputs();
    for (auto &audioDevice : qlistAudioDevice){
        qInfo() << "扬声器:" <<     audioDevice.description();
    }

}
void Qt6WangYonglin::QSoundPlayer::setSampleRate(int sampleRate){
    format.setSampleRate(sampleRate);
}
void Qt6WangYonglin::QSoundPlayer::setChannelCount(int channelCount){
    format.setChannelCount(channelCount);
}
void Qt6WangYonglin::QSoundPlayer::setSampleFormat(QAudioFormat::SampleFormat f){
    format.setSampleFormat(f);
}

QList<QAudioDevice> Qt6WangYonglin::QSoundPlayer::getAudioDevices()
{
    return qlistAudioDevice;
}

void Qt6WangYonglin::QSoundPlayer::closePlayer()
{
    if(qAudioSink){
        qAudioSink->stop();
        delete qAudioSink;
    }
}

void Qt6WangYonglin::QSoundPlayer::openPlayer(const QString &description)
{
    QAudioDevice info = QMediaDevices::defaultAudioOutput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    QList<QAudioDevice> listAudioDevice= qMediaDevices->audioOutputs();
    for (auto &audioDevice : listAudioDevice){
        if(audioDevice.description() == description){
            qAudioSink= new QAudioSink(audioDevice, format);
            qInfo() << tr("加载成功 扬声器[%1]").arg(description);
            qIODevice=qAudioSink->start();
            break;
        }
    }
}

void Qt6WangYonglin::QSoundPlayer::writePlayer(const QByteArray &audio_bytes)
{
    if(!audio_bytes.isEmpty() && qIODevice){
        qIODevice->write(audio_bytes);
    }
}

