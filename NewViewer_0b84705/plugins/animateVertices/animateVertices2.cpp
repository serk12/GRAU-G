#include "animateVertices.h"

void AnimateVertices::onPluginLoad()
{
	glwidget()->makeCurrent();
	time.start();
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
	"  frontColor=vec4(vec3(N.z),1);"
	"  gl_Position=modelViewProjectionMatrix*vec4(V, 1);"
	"}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src = 	
	"#version 330 core\n"
	"in vec4 vectColor;"
	"out vec4 fragColor;"
	"void main() {"
	"	fragColor = vectColor;"
	"}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

	program=new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;
}

void AnimateVertices::preFrame() 
{
	program->bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
	QMatrix3x3 NM  = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", NM); 
	program->setUniformValue("time", time.elapsed());

}

void AnimateVertices::postFrame() 
{
	program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(animateVertices, AnimateVertices)   // plugin name, plugin class
#endif

