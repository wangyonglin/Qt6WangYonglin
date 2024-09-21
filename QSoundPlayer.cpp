#include "QSoundPlayer.h"
#include <QDebug>
#include <QAudioSink>

Qt6WangYonglin::QSoundPlayer::QSoundPlayer(QObject *parent)
    : QObject{parent}
{
    qAudioFormat.setSampleRate(16000);
    qAudioFormat.setChannelCount(1);
    qAudioFormat.setSampleFormat(QAudioFormat::UInt8);
    qMediaDevices=new QMediaDevices(this);
    qlistAudioDevice= qMediaDevices->audioOutputs();
    for (auto &audioDevice : qlistAudioDevice){
        qInfo() << "扬声器:" <<     audioDevice.description();
    }

}


QList<QAudioDevice> Qt6WangYonglin::QSoundPlayer::getAudioDevices()
{
    return qlistAudioDevice;
}

void Qt6WangYonglin::QSoundPlayer::init(const QAudioFormat &format)
{
    qAudioFormat=format;
}

QAudioFormat Qt6WangYonglin::QSoundPlayer::format()
{
    return qAudioFormat;
}

void Qt6WangYonglin::QSoundPlayer::destroy()
{
    if(qAudioSink){
        qAudioSink->stop();
        delete qAudioSink;
    }
}

void Qt6WangYonglin::QSoundPlayer::create(const QString &desc)
{
    QAudioDevice info = QMediaDevices::defaultAudioOutput();
    if (!info.isFormatSupported(qAudioFormat)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    QList<QAudioDevice> listAudioDevice= qMediaDevices->audioOutputs();
    for (auto &audioDevice : listAudioDevice){
        if(audioDevice.description() == desc){
            qAudioSink= new QAudioSink(audioDevice, qAudioFormat);
            qInfo() << tr("加载成功 扬声器[%1]").arg(desc);
            qIODevice=qAudioSink->start();
            break;
        }
    }
}

void Qt6WangYonglin::QSoundPlayer::write(const QByteArray &audio_bytes)
{
    if(!audio_bytes.isEmpty() && qIODevice){
        qIODevice->write(audio_bytes);
    }
}

