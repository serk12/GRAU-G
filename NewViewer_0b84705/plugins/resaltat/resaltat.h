#ifndef _RESALTAT_H
#define _RESALTAT_H

#include "basicplugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class Resaltat : public QObject, public BasicPlugin {

  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)

  void createBuffers();
  void generate_vbo(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size);
  void drawBoxes();

  GLuint textureID;
  QOpenGLShaderProgram* program;
  QOpenGLShader* vs;
  QOpenGLShader* fs;

  bool created;
  GLuint cubeVAO;
  GLuint verticesVBO;
  GLuint colorVBO;

public:
  void onPluginLoad();
  void postFrame();

};

#endif



