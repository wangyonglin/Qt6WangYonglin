#include "QWangAudioInput.h"

QWangAudioInput::QWangAudioInput(QObject *parent)
    : QWangThreader{parent},
    sampleRate(16000),
    channelCount(1),
    sampleSize(16)
{

}


bool QWangAudioInput::initContextFormat(int sampleRate,
                                    int channelCount,
                                    int sampleSize){
    qIODevice = nullptr;
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
    qIODevice = audioInput->start(); // 这里可以直接写入到文件，咱不用直接就是播放 audioInput->start(file);
    //qIODevice need to manual release, or will memory leak

    if (qIODevice) {
        qDebug() << "device available";
        loopStart();
        return true;
    }
    return false;
}


void QWangAudioInput::loopRunnable()
{
    if(isRunning() && qIODevice){
     QByteArray buffer= qIODevice->readAll();
        if(!buffer.isEmpty()){
          emit onRefreshFrame(buffer);
      }
    }
}

void QWangAudioInput::Start(int sampleRate, int channelCount,int sampleSize)
{

    if(initContextFormat(sampleRate,channelCount,sampleSize))
    {
         loopStart();
    }

}

void QWangAudioInput::Stop()
{
    qIODevice->close();
    qIODevice=nullptr;
    audioInput->stop();
    loopStop();
}


