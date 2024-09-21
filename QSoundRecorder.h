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
    void init(const QAudioFormat &format);
    void create(const QString &desc);
    void destroy();
    QAudioFormat format();

public slots:
    void readyRead();
private:
    QAudioFormat qAudioFormat;
    QMediaDevices *qMediaDevices;
    QAudioSource *qAudioSource;
    QIODevice *qIODevice;
    QList<QAudioDevice> qlistAudioDevice;
signals:
 void refresh(const QByteArray & bytes);
private slots:
    void handleStateChanged(QAudio::State newState);
};
}


#endif // QSOUNDRECORDER_H
