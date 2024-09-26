#include "QSoundPlayer.h"
#include <QDebug>
#include <QAudioSink>

Qt6WangYonglin::QSoundPlayer::QSoundPlayer(QObject *parent)
    : QObject{parent}
{
    defaultDevice = QMediaDevices::defaultAudioOutput();
    defaultFormat.setSampleRate(16000);
    defaultFormat.setChannelCount(1);
    defaultFormat.setSampleFormat(QAudioFormat::UInt8);
    qMediaDevices=new QMediaDevices(this);
    qlistAudioDevice= qMediaDevices->audioOutputs();
    for (auto &audioDevice : qlistAudioDevice){
        qInfo() << "可用扬声器:" <<     audioDevice.description();
    }

}


QList<QAudioDevice> Qt6WangYonglin::QSoundPlayer::getAudioDevices()
{
    return qlistAudioDevice;
}

void Qt6WangYonglin::QSoundPlayer::init(const QAudioFormat &format,const QString &description)
{
    defaultFormat=format;
    QList<QAudioDevice> listDevice= qMediaDevices->audioOutputs();
    for (auto &currentDevice : listDevice){
        if(currentDevice.description() == description){
            defaultDevice=currentDevice;
            break;
        }
    }
}

QAudioFormat Qt6WangYonglin::QSoundPlayer::format()
{
    return defaultFormat;
}

void Qt6WangYonglin::QSoundPlayer::destroy()
{
    if(qAudioSink){
        qAudioSink->stop();
        delete qAudioSink;
    }
}

void Qt6WangYonglin::QSoundPlayer::create()
{

    if (!defaultDevice.isFormatSupported(defaultFormat)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }
    qAudioSink= new QAudioSink(defaultDevice, defaultFormat,this);
    qInfo() << tr("加载成功 扬声器[%1]").arg(defaultDevice.description());
    qInfo() << tr("加载成功 扬声器sampleRate[%1]").arg(defaultFormat.sampleRate());
    qIODevice=qAudioSink->start();


}

void Qt6WangYonglin::QSoundPlayer::write(const QByteArray &audio_bytes)
{
    if(!audio_bytes.isEmpty() && qIODevice){
        qIODevice->write(audio_bytes);
    }
}

