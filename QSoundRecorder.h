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
public slots:
    void readChanged();
private:
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
