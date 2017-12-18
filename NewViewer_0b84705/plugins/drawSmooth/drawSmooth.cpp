#include "drawSmooth.h"
#include "glwidget.h"
#include <cmath>

void DrawSmooth::cleanUp()
{
    if (!VAOs.size()) return;

    glwidget()->glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
    glwidget()->glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
    glwidget()->glDeleteBuffers(indexBuffers.size(),  &indexBuffers[0]);
    glwidget()->glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
    glwidget()->glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);

    glwidget()->glDeleteVertexArrays(VAOs.size(), &VAOs[0]);

    coordBuffers.clear();
    normalBuffers.clear();
    indexBuffers.clear();
    stBuffers.clear();
    colorBuffers.clear();
    VAOs.clear();

    numIndices.clear();
}

DrawSmooth::~DrawSmooth()
{
    cleanUp();
}

void DrawSmooth::onSceneClear()
{
    cleanUp();
}

bool DrawSmooth::drawObject(int i)
{
    glwidget()->glBindVertexArray(VAOs[i]);
    glwidget()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
    glwidget()->glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);

    glwidget()->glBindVertexArray(0);
    glwidget()->glBindBuffer(GL_ARRAY_BUFFER,0);
    glwidget()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    return true;
}

bool DrawSmooth::drawScene()
{
    for(int i=0; i < (int)VAOs.size(); i++) // for each VAO (that is, for each object)
    {
        glwidget()->glBindVertexArray(VAOs[i]);
        glwidget()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
        glwidget()->glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);
    }

    glwidget()->glBindVertexArray(0);

    glwidget()->glBindBuffer(GL_ARRAY_BUFFER,0);
    glwidget()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    return true;
}

void DrawSmooth::onPluginLoad()
{
    this->glwidget()->clearScene();
}

void DrawSmooth::onObjectAdd()
{
    addVBO( scene()->objects().size() - 1 );
}

void DrawSmooth::addVBO(unsigned int currentObject)
{
    // Step 1: Create and fill the four arrays (vertex coords, vertex normals, and face indices)
    // This version:
    //  - each coord/normal will appear one time (one for each corner with unique normal)

    vector<float> vertices; // (x,y,z)    Final size: 3*number of vertices
    vector<float> normals;  // (nx,ny,nz) Final size: 3*number of vertices
    vector<float> st;       // (s,t)      Final size: 2*number of vertices
    vector<float> colors;   // (r,g,b)    Final size: 3*number of vertices
    vector<int> indices;    //            Final size: 3*number of triangles

    const Object& obj = scene()->objects()[currentObject];
    const vector<Face> &faces = obj.faces();
    const vector<Vertex> &verts = obj.vertices();

    vector<Vector> normalSum(verts.size(), Vector(0, 0, 0));
    vector<int> normalCount(verts.size(), 0);

    for (int i = 0; i < (int)faces.size(); ++i)
    {
        const Face &face = faces[i];
        const Vector &N = face.normal().normalized();
        for (int j = 0; j < face.numVertices(); ++j)
        {
            int index = face.vertexIndex(j);
            ++normalCount[index];
            normalSum[index] += N;
            indices.push_back(index);
        }
    }

    for (int i = 0; i < (int)verts.size(); ++i)
    {
        Point P = verts[i].coord();
        vertices.push_back(P.x()); vertices.push_back(P.y()); vertices.push_back(P.z());

        Vector N = normalSum[i]/normalCount[i];
        normals.push_back(N.x()); normals.push_back(N.y()); normals.push_back(N.z());

        float r = obj.boundingBox().radius();
        float s = Vector::dotProduct((1.0/r)*Vector(1, 0, 1), P);
        float t = Vector::dotProduct((1.0/r)*Vector(0, 1, 0), P);
        if (obj.vertices().size() == 81) // plane: special case for /assig models
        {
            s = 0.5f*(P.x() + 1.0);
            t = 0.5f*(P.y() + 1.0);
        }
        if (obj.vertices().size() == 386) // cube: special case for /assig models
        {
            s = Vector::dotProduct((1.0/2.0)*Vector(1, 0, 1), P);
            t = Vector::dotProduct((1.0/2.0)*Vector(0, 1, 0), P);
        }
        st.push_back(s);
        st.push_back(t);

        colors.push_back(abs(N.x()));
        colors.push_back(abs(N.y()));
        colors.push_back(abs(N.z()));
    }

    // Step 2: Create empty buffers (coords, normals, st, indices)
    GLuint VAO;
    glwidget()->glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glwidget()->glBindVertexArray(VAO);

    GLuint coordBufferID;
    glwidget()->glGenBuffers(1, &coordBufferID);
    coordBuffers.push_back(coordBufferID);

    GLuint normalBufferID;
    glwidget()->glGenBuffers(1, &normalBufferID);
    normalBuffers.push_back(normalBufferID);

    GLuint colorBufferID;
    glwidget()->glGenBuffers(1, &colorBufferID);
    colorBuffers.push_back(colorBufferID);

    GLuint stBufferID;
    glwidget()->glGenBuffers(1, &stBufferID);
    stBuffers.push_back(stBufferID);

    GLuint indexBufferID;
    glwidget()->glGenBuffers(1, &indexBufferID);
    indexBuffers.push_back(indexBufferID);

    numIndices.push_back(indices.size());

    // Step 3: Define VBO data (coords, normals, indices)
    glwidget()->glBindBuffer(GL_ARRAY_BUFFER, coordBuffers[currentObject]);
    glwidget()->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glwidget()->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
    glwidget()->glEnableVertexAttribArray(0);

    glwidget()->glBindBuffer(GL_ARRAY_BUFFER, normalBuffers[currentObject]);
    glwidget()->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
    glwidget()->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
    glwidget()->glEnableVertexAttribArray(1);

    glwidget()->glBindBuffer(GL_ARRAY_BUFFER, colorBuffers[currentObject]);
    glwidget()->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
    glwidget()->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
    glwidget()->glEnableVertexAttribArray(2);

    glwidget()->glBindBuffer(GL_ARRAY_BUFFER, stBuffers[currentObject]);
    glwidget()->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*st.size(), &st[0], GL_STATIC_DRAW);
    glwidget()->glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
    glwidget()->glEnableVertexAttribArray(3);

    glwidget()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[currentObject]);
    glwidget()->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

    glwidget()->glBindVertexArray(0);
    glwidget()->glBindBuffer(GL_ARRAY_BUFFER,0);
    glwidget()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2(drawSmooth, DrawSmooth)   // plugin name, plugin class
#endif



