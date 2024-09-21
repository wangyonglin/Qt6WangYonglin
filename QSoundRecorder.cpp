#include "QSoundRecorder.h"

#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSource>
#include <QDebug>

Qt6WangYonglin::QSoundRecorder::QSoundRecorder(QObject *parent)
    :QObject(parent)
{
    qAudioFormat.setSampleRate(16000);
    qAudioFormat.setChannelCount(1);
    qAudioFormat.setSampleFormat(QAudioFormat::UInt8);
    qMediaDevices=new QMediaDevices(this);
    qlistAudioDevice= qMediaDevices->audioInputs();
    for (auto &audioDevice : qlistAudioDevice){
        qInfo() << "麦克风:" <<     audioDevice.description();
    }

}

QList<QAudioDevice> Qt6WangYonglin::QSoundRecorder::getAudioDevices(){
    return qlistAudioDevice;
}

void Qt6WangYonglin::QSoundRecorder::init(const QAudioFormat &format)
{
    qAudioFormat=format;
}


void Qt6WangYonglin::QSoundRecorder::create(const QString & desc)
{

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(qAudioFormat)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    QList<QAudioDevice> listAudioDevice= qMediaDevices->audioInputs();
    for (auto &audioDevice : listAudioDevice){
        if(audioDevice.description() == desc){
            qAudioSource = new QAudioSource(audioDevice,qAudioFormat, this);
            connect(qAudioSource, &QAudioSource::stateChanged, this, &QSoundRecorder::handleStateChanged);
            qInfo() << tr("加载成功 麦克风[%1]").arg(desc);
            qIODevice=qAudioSource->start();
            connect(qIODevice,&QIODevice::readyRead,this,&Qt6WangYonglin::QSoundRecorder::readyRead);
            break;
        }
    }


}

void Qt6WangYonglin::QSoundRecorder::readyRead()
{
    if(qIODevice){
        emit refresh(qIODevice->readAll());
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

void Qt6WangYonglin::QSoundRecorder::destroy(){
    if(qAudioSource){
        qAudioSource->stop();
        delete qAudioSource;
    }
}

QAudioFormat Qt6WangYonglin::QSoundRecorder::format()
{
    return qAudioFormat;
}

