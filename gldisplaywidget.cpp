#include "gldisplaywidget.h"


#ifdef __APPLE__
    #include <glu.h>
#else
//    #include <gl/GL.h>
    #include <GL/gl.h>
#endif

#include <GL/glu.h>
#include "QDebug"
#include "Iterator.h"
#include <iostream>

using namespace std;

void GLDisplayWidget::test() {
    // loadMesh("flat");
    // cout << "nb face depart " << _mesh.getFaces().size() << endl;
    // cout << "let's go " << _mesh.simplify(10) << endl;
    // cout << "nb face apres " << _mesh.getFaces().size() << endl;

    // _mesh.collapse(0,6);
    // _mesh.collapse(10,9);
    // for (int i = 0; i < _mesh.getFaces().size(); i++) {
    //     _mesh.getFaces()[i].display();
    // }

    // cout << "vertices supp " << endl;
    // for (int i = 0; i < _mesh.deletedVertices.size(); i++) {
    //     cout <<_mesh.deletedVertices[i] << endl;
    // }
    // cout << "faces supp " << endl;
    // for (int i = 0; i < _mesh.deletedFaces.size(); i++) {
    //     cout << _mesh.deletedFaces[i] << endl;
    // }

    /*
    cout << "hey we gonna debug here ! " << endl;

    Iterator_on_vertices its;
    Circulator_on_faces cf ;
    int i = 0;
    for (its = _mesh.vertices_begin(); its != _mesh.vertices_past_the_end(); ++its) {
        // cout << "vertice " << i << endl;
        Circulator_on_faces cfbegin = _mesh.incident_faces(*its);
        int cmpt = 0 ;
        for (cf=cfbegin,++cf; cf!=cfbegin; cf++) {
            cmpt++ ;
            cout << "cmpt = " << cmpt << endl;
        }
        i++;
        std::cout<< "valence of the vertex" << cmpt << std::endl;
    }
    */
    

    // Test value of new faces
    // cout << "size face " << titi.getFaces().size() << endl;
    // for (int i = 0; i < 8; i++) {
    //     _mesh.getFaces()[i].display();
    // }

    // Circulator_on_faces cf;
    // Circulator_on_faces cfbegin = titi.incident_faces(*its);
    // for (cf=cfbegin,++cf; cf!=cfbegin; cf++) {

    // }


    // Test circulator_on_vertices
    // Mesh titi;
    // int cmpt = 0 ;
    // Circulator_on_vertices cv;
    // Circulator_on_vertices cvbegin = titi.adjacent_vertices(titi.getVertices()[4]);
    // for (cv=cvbegin,++cv; cv!=cvbegin; cv++) cmpt++;
    //     std::cout<< "valence of the vertex" << cmpt << std::endl;

    // cout << "end of debug " << endl;


}


GLDisplayWidget::GLDisplayWidget(QWidget *parent) : QGLWidget(parent)
{
    // Update the scene
    connect( &_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    _timer.start(16);
}

void GLDisplayWidget::initializeGL()
{
    // background color
    glClearColor(0.2, 0.2, 0.2, 1);

    // Shader
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Construction of the mesh before it is displayed
    // To add....
    test();
}



void GLDisplayWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Center the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,  0,0,0,   0,1,0);

    // Translation
    glTranslated(_X, _Y, _Z);

    // Rotation
    glRotatef(_angle, 1.0f, 1.0f, 0.0f);

    // Color for your mesh
    glColor3f(0, 1 ,0);

    // example with a tetraedre
    if (_wireframe) _mesh.drawMeshWireFrame();
    else _mesh.drawMesh();
}

void GLDisplayWidget::resizeGL(int width, int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    updateGL();
}

// - - - - - - - - - - - - Mouse Management  - - - - - - - - - - - - - - - -
// When you click, the position of your mouse is saved
void GLDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _lastPosMouse = event->pos();
}

// Mouse movement management
void GLDisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - _lastPosMouse.x();
    // int dy = event->y() - lastPosMouse.y();

    if( event != NULL )
    {
        _angle += dx;
        _lastPosMouse = event->pos();

        updateGL();
    }
}

// Mouse Management for the zoom
void GLDisplayWidget::wheelEvent(QWheelEvent *event) {
    QPoint numDegrees = event->angleDelta();
    double stepZoom = 0.25;
    if (!numDegrees.isNull())
    {
      _Z = (numDegrees.x() > 0 || numDegrees.y() > 0) ? _Z + stepZoom : _Z - stepZoom;
    }
}

void GLDisplayWidget::setWireframe(bool value) {
    _wireframe = value;
}

void GLDisplayWidget::insert(double x, double y, double z) {
    _mesh.insert(Point(x,y,z));
}

void GLDisplayWidget::flip(int faceA, int faceB) {
    _mesh.flip(faceA, faceB);
}

void GLDisplayWidget::collapse(int face, int p) {
    _mesh.collapse(face,p);
}

void GLDisplayWidget::loadMesh(std::string name) {
    std::string path = "../Mesh_Computational_Geometry/";
    _mesh.load_mesh(path + name + ".off");
}

void GLDisplayWidget::clean() {
    _mesh.clean();
}

void GLDisplayWidget::simplify(int nb) {
    _mesh.simplify(nb);
}