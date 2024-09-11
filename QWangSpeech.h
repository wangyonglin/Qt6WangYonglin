#ifndef KYLINMICROPHONE_H
#define KYLINMICROPHONE_H

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
#include <QObject>
#include "QWangThreader.h"
#include "QtWangYonglin_global.h"

class QTWANGYONGLIN_EXPORT QWangSpeech : public QWangThreader
{
    Q_OBJECT
public:
    explicit QWangSpeech(QObject *parent = nullptr);
    ~QWangSpeech();
public slots:
    bool StartPlayer(int sampleRate, int channelCount, int sampleSize);
    void StopPlayer();
signals:
    void onRefreshFrame(QByteArray buffer);
private:
    bool initContextFormat(int sampleRate=16000,
                        int channelCount=1,
                        int sampleSize=16);
private:
    QAudioInput* audioInput;
    QIODevice *qIODevice;
    int sampleRate;
    int channelCount;
    int sampleSize;
protected:
    virtual void loopRunnable() override;
};

#endif
