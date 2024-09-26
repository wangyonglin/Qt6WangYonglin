#include "QSoundRecorder.h"

#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSource>
#include <QDebug>

Qt6WangYonglin::QSoundRecorder::QSoundRecorder(QObject *parent)
    :QObject(parent)
{
    defaultDevice = QMediaDevices::defaultAudioInput();
    defaultFormat.setSampleRate(16000);
    defaultFormat.setChannelCount(1);
    defaultFormat.setSampleFormat(QAudioFormat::Int16);
    defaultFormat.setChannelConfig(QAudioFormat::ChannelConfigStereo);
    qMediaDevices=new QMediaDevices(this);
    qlistAudioDevice= qMediaDevices->audioInputs();
    for (auto &audioDevice : qlistAudioDevice){
        qInfo() << "可用麦克风:" <<     audioDevice.description();
    }

}

QList<QAudioDevice> Qt6WangYonglin::QSoundRecorder::getAudioDevices(){
    return qlistAudioDevice;
}

void Qt6WangYonglin::QSoundRecorder::init(const QAudioFormat &format, const QString &description)
{
    if(format.isValid()){
        defaultFormat=format;
    }
    QList<QAudioDevice> listAudioDevice= qMediaDevices->audioInputs();
    for (auto &listDevice : listAudioDevice){
        if(listDevice.description() == description){
            defaultDevice=listDevice;
            break;
        }
    }

}




void Qt6WangYonglin::QSoundRecorder::create()
{

    if(defaultDevice.isNull()){
        defaultDevice== QMediaDevices::defaultAudioInput();
    }
    if (!defaultDevice.isFormatSupported(defaultFormat)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }
    qAudioSource = new QAudioSource(defaultDevice,defaultFormat, this);
    if(qAudioSource){
        connect(qAudioSource, &QAudioSource::stateChanged, this, &QSoundRecorder::handleStateChanged);
        qInfo() << tr("加载成功 麦克风名称[%1]").arg(defaultDevice.description());
        qInfo() << tr("加载成功 sampleRate[%1]").arg(defaultFormat.sampleRate());
        qIODevice=qAudioSource->start();
        connect(qIODevice,&QIODevice::readyRead,this,&Qt6WangYonglin::QSoundRecorder::readyRead);
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
    return defaultFormat;
}

