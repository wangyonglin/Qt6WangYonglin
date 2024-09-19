#ifndef QSOUNDRECORDER_H
#define QSOUNDRECORDER_H


#include "QtWangYonglin_global.h"
#include <QMediaDevices>
#include <QAudioSource>

namespace Qt6WangYonglin {
class QTWANGYONGLIN_EXPORT QSoundRecorder : public QObject
{
    Q_OBJECT
public:
    explicit QSoundRecorder(QObject *parent = nullptr);
    QList<QAudioDevice> getAudioDevices();
    void closeRecorder();
    void openRecorder(const QString &description);
    void setSampleRate(int sampleRate);
    void setChannelCount(int channelCount);
    void setSampleFormat(QAudioFormat::SampleFormat f);
public slots:
    void readChanged();
private:
    QAudioFormat format;
    QMediaDevices *qMediaDevices;
    QAudioSource *qAudioSource;
    QIODevice *qIODevice;
    QList<QAudioDevice> qlistAudioDevice;
signals:
 void readRecorder(const QByteArray & data);
private slots:
    void handleStateChanged(QAudio::State newState);
};
}


#endif // QSOUNDRECORDER_H
