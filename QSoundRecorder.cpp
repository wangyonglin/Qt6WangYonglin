#include "QSoundRecorder.h"

#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSource>
#include <QDebug>

Qt6WangYonglin::QSoundRecorder::QSoundRecorder(QObject *parent)
    :QObject(parent)
{
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::UInt8);
    qMediaDevices=new QMediaDevices(this);
    qlistAudioDevice= qMediaDevices->audioInputs();
    for (auto &audioDevice : qlistAudioDevice){
        qInfo() << "麦克风:" <<     audioDevice.description();
    }

}

QList<QAudioDevice> Qt6WangYonglin::QSoundRecorder::getAudioDevices(){
    return qlistAudioDevice;
}


void Qt6WangYonglin::QSoundRecorder::openRecorder(const QString & description)
{

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    QList<QAudioDevice> listAudioDevice= qMediaDevices->audioInputs();
    for (auto &audioDevice : listAudioDevice){
        if(audioDevice.description() == description){
            qAudioSource = new QAudioSource(audioDevice,format, this);
            connect(qAudioSource, &QAudioSource::stateChanged, this, &QSoundRecorder::handleStateChanged);
            qInfo() << tr("加载成功 麦克风[%1]").arg(description);
            qIODevice=qAudioSource->start();
            connect(qIODevice,&QIODevice::readyRead,this,&Qt6WangYonglin::QSoundRecorder::readChanged);
            break;
        }
    }


}

void Qt6WangYonglin::QSoundRecorder::readChanged()
{
    if(qIODevice){
        emit readRecorder(qIODevice->readAll());
    }
}



void Qt6WangYonglin::QSoundRecorder::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
    case QAudio::StoppedState:
        if (qAudioSource->error() != QAudio::NoError) {
            qDebug()<<"录音出现错误.\n";
        } else {
            qInfo()<<"完成录音\n";
        }
        break;

    case QAudio::ActiveState:
        qInfo()<<"开始从IO设备读取PCM声音数据.\n";
        break;

    default:
        // ... other cases as appropriate
        break;
    }
}

void Qt6WangYonglin::QSoundRecorder::closeRecorder(){
    if(qAudioSource){
        qAudioSource->stop();
        delete qAudioSource;
    }
}

void Qt6WangYonglin::QSoundRecorder::setSampleRate(int sampleRate){
    format.setSampleRate(sampleRate);
}
void Qt6WangYonglin::QSoundRecorder::setChannelCount(int channelCount){
    format.setChannelCount(channelCount);
}
void Qt6WangYonglin::QSoundRecorder::setSampleFormat(QAudioFormat::SampleFormat f){
    format.setSampleFormat(f);
}
