#include "reflection.h"
#include <QCoreApplication>

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Reflection::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./plugins/reflection/reflection.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./plugins/reflection/reflection.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    // Setup texture
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureId);
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		      GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT,
		   0, GL_RGB, GL_FLOAT, NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);

    mirrorCreated = false;
}

void Reflection::onObjectAdd(){
    mirrorCreated = false;
}

void Reflection::drawMirror(){
    static GLuint VAO_rect;

    if(!mirrorCreated){
        mirrorCreated = true;
        glwidget()->glGenVertexArrays(1, &VAO_rect);
        glwidget()->glBindVertexArray(VAO_rect);

        Point min = scene()->boundingBox().min();
        Point max = scene()->boundingBox().max();

        float a = 1.5;
        float xmin = min.x()*a;
        float ymin = min.y();
        float zmin = min.z()*a;
        float xmax = max.x()*a;
        float zmax = max.z()*a;

        float coords[] = {  xmin, ymin, zmin,
                            xmax, ymin, zmin,
                            xmin, ymin, zmax,
                            xmax, ymin, zmax};
        GLuint VBO_coords;
        glwidget()->glGenBuffers(1, &VBO_coords);
        glwidget()->glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        glwidget()->glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        glwidget()->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glwidget()->glEnableVertexAttribArray(0);
        glwidget()->glBindVertexArray(0);
    }
    glwidget()->glBindVertexArray (VAO_rect);
    glwidget()->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glwidget()->glBindVertexArray(0);
}

QMatrix4x4 reflectionMatrix(QVector4D plane){
    float a = plane.x();
    float b = plane.y();
    float c = plane.z();
    float d = plane.w();
  
    return QMatrix4x4(
           1-2*a*a, -2*b*a,   -2*c*a,   -2*d*a,
          -2*b*a,    1-2*b*b, -2*c*b,   -2*d*b,
          -2*c*a,   -2*c*b,    1-2*c*c, -2*d*c,
           0,        0,        0,        1
    );
}

bool Reflection::paintGL()
{
    // Pass 1. Draw scene
    glwidget()->glClearColor(1,1,1,1);
    glwidget()->glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    program->bind();

    Box b = scene()->boundingBox();
    float r = b.radius();
    float a = 2;
    b.expand(Box(b.min()-a*QVector3D(r,r,r), b.max()+a*QVector3D(r,r,r)));
    camera()->updateClippingPlanes(b);
    
        // Step 1: draw mirrored scene in a texture 
    float d = scene()->boundingBox().min().y();
    QVector4D plane = QVector4D(0,-1,0,d);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("useTexture", false);
    program->setUniformValue("modelViewProjectionMatrix", MVP * reflectionMatrix(plane));
    if (drawPlugin()) drawPlugin()->drawScene();

    // Get texture
    glwidget()->glBindTexture(GL_TEXTURE_2D, textureId);
    glwidget()->glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT); // copies from back buffer
    glwidget()->glGenerateMipmap(GL_TEXTURE_2D);
    // Clear framebuffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Step 2: draw scene
    program->setUniformValue("useTexture", false);
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    if (drawPlugin()) drawPlugin()->drawScene();
    
    // Step 3: Draw textured mirror
    program->setUniformValue("useTexture", true);
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("SIZE", float(IMAGE_WIDTH));
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    drawMirror();
    
    program->release();
    glwidget()->glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}
