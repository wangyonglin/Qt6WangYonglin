#include "QWangOpenGL.h"
#include <QResizeEvent>

QWangOpenGL::QWangOpenGL(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

void QWangOpenGL::initializeGL()
{
    initializeOpenGLFunctions(); //初始化OPenGL功能函数
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);     //设置纹理2D功能可用


    if(!program->addShaderFromSourceFile(QOpenGLShader::Vertex,tr(":/opengl/image.vsh")))
    {
        close();
    }

    if(!program->addShaderFromSourceFile(QOpenGLShader::Fragment,tr(":/opengl/image.fsh")))
    {
        close();
    }

    program->bindAttributeLocation("vertex", 0);//绑定顶点属性位置
    program->bindAttributeLocation("texCoord", 1);//绑定纹理属性位置
    // 链接着色器管道
    if (!program->link())
    {
        close();
    }

    // 绑定着色器管道
    if (!program->bind())
    {
        close();
    }

    //纹理坐标
    texCoords.append(QVector2D(0, 1)); //左上
    texCoords.append(QVector2D(1, 1)); //右上
    texCoords.append(QVector2D(0, 0)); //左下
    texCoords.append(QVector2D(1, 0)); //右下
    //顶点坐标
    vertices.append(QVector3D(-1, -1, 1));//左下
    vertices.append(QVector3D(1, -1, 1)); //右下
    vertices.append(QVector3D(-1, 1, 1)); //左上
    vertices.append(QVector3D(1, 1, 1));  //右上

    // 加载 Avengers.jpg 图片
    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setFormat(QOpenGLTexture::RGBFormat);
    //重复使用纹理坐标
    //纹理坐标(1.1, 1.2)与(0.1, 0.2)相同
    texture->setWrapMode(QOpenGLTexture::Repeat);
    //设置纹理大小
    texture->setSize(width(),height());

    //分配储存空间
    texture->allocateStorage();
}

void QWangOpenGL::resizeGL(int width, int height)
{
    // 计算窗口横纵比
    qreal aspect = qreal(width) / qreal(height ? height : 1);
    // 设置近平面值 3.0, 远平面值 7.0, 视场45度
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    // 重设投影
    projection.setToIdentity();
    // 设置透视投影
    projection.perspective(fov, static_cast<float>(aspect), zNear, zFar);
}

void QWangOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕缓存和深度缓冲
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);                   //矩阵变换
    program->setAttributeArray(0, vertices.constData());
    program->enableAttributeArray(0);
    program->setAttributeArray(1, texCoords.constData());
    program->enableAttributeArray(1);
    program->setUniformValue("texture", 0); //将当前上下文中位置的统一变量设置为value
    if(!dstQImage.isNull()){
        texture->setData(dstQImage); //设置纹理图像
    }
    texture->bind();  //绑定纹理
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//绘制纹理
    texture->release(); //释放绑定的纹理
    texture->destroy(); //消耗底层的纹理对象
    texture->create();
}


void QWangOpenGL::onRefreshFrame(const QImage &image)
{

    if(image.isNull())return;
    dstQImage =image.scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(!dstQImage.isNull())
    {
        update();
    }

}
void QWangOpenGL::resizeEvent(QResizeEvent *event)
{
    resize(event->size());
    resizeGL(width(),height());
}
