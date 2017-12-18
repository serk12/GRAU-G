#ifndef _SHADOWMAP_H
#define _SHADOWMAP_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class ShadowMap : public QObject, public BasicPlugin
 {
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    bool paintGL();
    void keyPressEvent(QKeyEvent*);   
 
 private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureId;
    Camera lightCamera;

    void drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3);
 };
 
 #endif
