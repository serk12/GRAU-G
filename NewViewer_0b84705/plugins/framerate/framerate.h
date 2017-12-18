#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include "basicplugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QElapsedTimer>

class Framerate : public QObject, public BasicPlugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif     
     Q_INTERFACES(BasicPlugin)

 public:
    void postFrame() Q_DECL_OVERRIDE;
    void onPluginLoad() Q_DECL_OVERRIDE;
	
 private:
    GLuint textureID;
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
	QElapsedTimer timer;
	QTimer timer2;
 };
 
 #endif
