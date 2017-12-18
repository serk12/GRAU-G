#ifndef _ANIMATEVERTICES_H
#define _ANIMATEVERTICES_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>

      
class AnimatePlugin : public QObject, public BasicPlugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "AnimatePlugin")   
#endif     
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad() Q_DECL_OVERRIDE;
    void preFrame() Q_DECL_OVERRIDE;
    void postFrame() Q_DECL_OVERRIDE;
 private:
    QElapsedTimer elapsedTimer;
    QTimer timer; 
    QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs; 
 };
 
 #endif

