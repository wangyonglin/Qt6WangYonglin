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
    void closePlayer();
    void openPlayer(const QString &description);

public slots:
    void writePlayer(const QByteArray &data);

private:
    QMediaDevices *qMediaDevices;
    QAudioSink* qAudioSink;
    QIODevice *qIODevice;
    QList<QAudioDevice> qlistAudioDevice;
signals:
};
}
#endif // QSOUNDPLAYER_H
