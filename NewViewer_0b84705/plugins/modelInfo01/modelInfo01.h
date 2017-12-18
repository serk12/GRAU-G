#ifndef _MODELINFO01_H
#define _MODELINFO01_H

#include "basicplugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class ModelInfo01 : public QObject, public BasicPlugin
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
 };
 
 #endif
