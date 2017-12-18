#ifndef _RESALTATMOUSE_H
#define _RESALTATMOUSE_H

#include "basicplugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class ResaltatMouse : public QObject, public BasicPlugin {

  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)

  void createBuffers();
  void generate_vbo(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size);
  void drawBoxes();

  GLuint textureID;
  QOpenGLShaderProgram* program, *programColor;
  QOpenGLShader* vs, *vs2;
  QOpenGLShader* fs, *fs2;

  bool created;
  GLuint cubeVAO;
  GLuint verticesVBO;
  GLuint colorVBO;

  int index;

public:
  void onPluginLoad();
  void postFrame();
  void mouseReleaseEvent(QMouseEvent* e); 	

};

#endif



