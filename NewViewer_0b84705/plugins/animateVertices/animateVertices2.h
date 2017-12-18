#ifndef _ANIMATEVERTICES_H
#define _ANIMATEVERTICES_H

#include "basicplugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QTime>

class AnimateVertices : public QObject, public BasicPlugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif     
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void preFrame();
    void postFrame();
	
    
 private:
	QTime time;
	GLuint vertexVAO;
	GLuint verticesVBO;
    QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs; 
 };
 
 #endif
