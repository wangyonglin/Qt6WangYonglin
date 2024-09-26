#ifndef QSOUNDPLAYER_H
#define QSOUNDPLAYER_H

#include <QObject>
#include "Qt6WangYonglin_global.h"
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>

namespace Qt6WangYonglin {

class QT6WANGYONGLIN_EXPORT QSoundPlayer : public QObject
{
    Q_OBJECT
public:
    explicit QSoundPlayer(QObject *parent = nullptr);
    QList<QAudioDevice> getAudioDevices();
    QAudioFormat format();
    void destroy();
    void init(const QAudioFormat &format, const QString &description=nullptr);
    void create();
public slots:
    void write(const QByteArray &data);

private:
    QAudioDevice defaultDevice;
    QAudioFormat defaultFormat;
    QMediaDevices *qMediaDevices;
    QAudioSink* qAudioSink;
    QIODevice *qIODevice;
    QList<QAudioDevice> listDevices;
signals:
};
}
#endif // QSOUNDPLAYER_H
