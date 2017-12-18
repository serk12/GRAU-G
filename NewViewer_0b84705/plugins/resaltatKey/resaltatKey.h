#ifndef _RESALTATKEY_H
#define _RESALTATKEY_H

#include "basicplugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class ResaltatKey : public QObject, public BasicPlugin {

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

  int i;

public:
  void onPluginLoad();
  void postFrame();
  void keyPressEvent(QKeyEvent* e); 	

};

#endif



