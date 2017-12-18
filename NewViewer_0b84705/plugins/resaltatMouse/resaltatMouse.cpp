#include "resaltatMouse.h"

void ResaltatMouse::onPluginLoad() {
  	// Carregar shader, compile & link 
  glwidget()->makeCurrent();
  vs=new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs->compileSourceFile("./plugins/boundingBox/boundingBox.vert");
  fs=new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs->compileSourceFile("./plugins/boundingBox/boundingBox.frag");
  program=new QOpenGLShaderProgram(this);
  program->addShader(vs);
  program->addShader(fs);
  program->link();

  vs2 = new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs2->compileSourceFile("./plugins/resaltatMouse/resaltatMouse.vert");
  fs2 = new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs2->compileSourceFile("./plugins/resaltatMouse/resaltatMouse.frag");
  programColor=new QOpenGLShaderProgram(this);
  programColor->addShader(vs2);
  programColor->addShader(fs2);
  program->link();

  created=false;
  index = -1;

}

void ResaltatMouse::mouseReleaseEvent(QMouseEvent* e) {
	if (! (e->button() & Qt::RightButton)) return;
	if ( e->modifiers() & (Qt::ShiftModifier)) return;
	if (! (e->modifiers() & Qt::ControlModifier)) return;
  glwidget()->makeCurrent();	
  glwidget()->glClearColor(1, 1, 1, 1);                           // esborrar els buffers amb un color de fons únic (blanc)
  glwidget()->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  programColor->bind();
  QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
  programColor->setUniformValue("modelViewProjectionMatrix", MVP);
  for (unsigned int i=0; i<scene()->objects().size(); ++i) { 
    programColor->setUniformValue("colorSelect", QVector4D(i/255., i/255., i/255., 1));
    drawPlugin()->drawObject(i);
  }
  programColor->release();

  int x = e->x();
	int y = glwidget()->height()-e->y();
	GLubyte read[4];
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
	index = int(read[0]);                       
  glwidget()->update();	
}

void ResaltatMouse::generate_vbo(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size) {
  glwidget()->glGenBuffers(1, &vbo_id);
  glwidget()->glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glwidget()->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, data, GL_STATIC_DRAW);
  glwidget()->glVertexAttribPointer(attribute_id, attribute_size, GL_FLOAT, GL_FALSE, 0, 0);
  glwidget()->glEnableVertexAttribArray(attribute_id);
}

void ResaltatMouse::createBuffers() {
  // dades
  GLfloat cube_vertices[]={
    1, 1, 1,
    0, 1, 1,
    1, 0, 1,
    0, 0, 1,
    1, 0, 0,
    0, 0, 0,
    1, 1, 0,
    0, 1, 0,
    1, 1, 1,
    0, 1, 1,
    0, 1, 1,
    0, 1, 0,
    0, 0, 1,
    0, 0, 0,
    1, 0, 1,
    1, 0, 0,
    1, 1, 1,
    1, 1, 0
  };
  GLfloat cube_colors[]={
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0
  };
  // VAO Capsa
  glwidget()->glGenVertexArrays(1, &cubeVAO);
  glwidget()->glBindVertexArray(cubeVAO);
  // VBOs Capsa
  generate_vbo(verticesVBO, 18*3, &cube_vertices[0], 0, 3);
  generate_vbo(colorVBO, 18*3, &cube_colors[0], 2, 3);
}

void ResaltatMouse::drawBoxes() {
  // crear buffers
  if (!created) {
    created=true;
    createBuffers();
  }
  
  // establir modelViewProjection
  QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
  program->setUniformValue("modelViewProjectionMatrix", MVP);
  
  Scene* scn=scene();
  const vector<Object> &obj=scn->objects();
  if(index > -1 && (int)obj.size() > index) {
    // pintar la capsa contenidora de tots els objectes de l'escena
    program->setUniformValue("boundingBoxMin",obj[index].boundingBox().min());
    program->setUniformValue("boundingBoxMax",obj[index].boundingBox().max());
    glwidget()->glBindVertexArray(cubeVAO);
    glwidget()->glDrawArrays(GL_TRIANGLE_STRIP, 0, 18);
    glwidget()->glBindVertexArray(0);
  }

}

void ResaltatMouse::postFrame() { 
  program->bind();
  GLint polygonMode;                              // en que polygon mode estamos? (GL_LINE, GL_FILL, GL_POINTS)
  glwidget()->glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
  glwidget()->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      // pinta el wireframe
  drawBoxes();                                    // de las cajas contenedoras de todos los objetos de la escena
  glwidget()->glPolygonMode(GL_FRONT_AND_BACK, polygonMode);  // reestablecer el poygon mode anterior
  program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(resaltatMouse, ResaltatMouse)   // plugin name, plugin class
#endif

