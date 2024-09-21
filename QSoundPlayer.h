#ifndef QSOUNDPLAYER_H
#define QSOUNDPLAYER_H

#include <QObject>
#include "QtWangYonglin_global.h"
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>

namespace Qt6WangYonglin {

class QTWANGYONGLIN_EXPORT QSoundPlayer : public QObject
{
    Q_OBJECT
public:
    explicit QSoundPlayer(QObject *parent = nullptr);
    QList<QAudioDevice> getAudioDevices();
    void init(const QAudioFormat &format);
    QAudioFormat format();
    void create(const QString &desc);
    void destroy();
public slots:
    void write(const QByteArray &data);

private:
    QAudioFormat qAudioFormat;
    QMediaDevices *qMediaDevices;
    QAudioSink* qAudioSink;
    QIODevice *qIODevice;
    QList<QAudioDevice> qlistAudioDevice;
signals:
};
}
#endif // QSOUNDPLAYER_H
