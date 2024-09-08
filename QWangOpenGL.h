#ifndef QWANGOPENGL_H
#define QWANGOPENGL_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>
#include <mutex>
#include "QtWangYonglin_global.h"

class QTWANGYONGLIN_EXPORT QWangOpenGL : public QOpenGLWidget,public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit QWangOpenGL(QWidget *parent = nullptr);
public:
       QImage dstQImage;
public slots:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    virtual void onRefreshFrame(const QImage &image);
private:
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
    QOpenGLShaderProgram *program;
    QOpenGLTexture *texture;
    QMatrix4x4 projection;

signals:
    void finished();
    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;

};

#endif // QWANGOPENGL_H
