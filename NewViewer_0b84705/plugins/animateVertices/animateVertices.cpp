#include "animateVertices.h"


void AnimatePlugin::onPluginLoad() {
    glwidget()->makeCurrent();
    // Carregar shader, compile & link 
    QString vs_src =
	"#version 330 core\n"
	"layout (location = 0) in vec3 vertex;"
	"layout (location = 1) in vec3 normal;"
	"layout (location = 2) in vec3 color;"
	"layout (location = 3) in vec2 texCoord;"

	"out vec4 frontColor;"
	"out vec2 vtexCoord;"

	"uniform mat4 modelViewProjectionMatrix;"
	"uniform mat3 normalMatrix;"

	"uniform float time;"
	"uniform float amplitude=0.1;"
	"uniform float freq=1;"

	"float PI=acos(-1.0);"
	 
	"void main() {"
	"  vec3 V=vertex+normal*abs(amplitude*sin(PI*2*freq*time));"
	"  vec3 N = normalize(normalMatrix * normal);"
	"  frontColor=vec4(N,1);"
	"  gl_Position=modelViewProjectionMatrix*vec4(V, 1);"
	"}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);

    QString fs_src = 	
	"#version 330 core\n"
	"in vec4 frontColor;"
	"out vec4 fragColor;"
	"void main() {"
	"	fragColor = frontColor;"
	"}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
    
    connect(&timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
    timer.start();
    elapsedTimer.start();
}

void AnimatePlugin::preFrame() {
    program->bind();
    
    //bindejar atributs i uniforms!
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
    
    //program->setUniformValue("amplitude", 0.1);
    //program->setUniformValue("freq", 0.1);
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0));
}

void AnimatePlugin::postFrame() {
    program->release();
}

#if QT_VERSION < 0x050000
                
Q_EXPORT_PLUGIN2(animatePlugin, AnimatePlugin)   // plugin name, plugin class
#endif

