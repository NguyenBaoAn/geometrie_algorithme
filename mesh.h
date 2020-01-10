#ifndef MESH_H
#define MESH_H

#include <QGLWidget>
#include "Iterator.h"
#include <QVector3D>
#include <string>


// TO MODIFY
// Advice => You should create a new file for each module but not necessarily for each class
class Point
{
    double _x;
    double _y;
    double _z;


public:
    Point():_x(),_y(),_z() {}
    Point(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_) {}
    // get
    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }

    bool operator==(Point p);
    void display();
};


class Vertice
{
    Point _coordinate;
    int _incidentFace;

public:
    Vertice();
    Vertice(float x, float y, float z, int incidentFace);

    //get
    Point getCoordinate();

    void setIncidentFace(int f);

    int getIncidentFace();

    bool operator==(Vertice v);
};


class Face
{
    // Supposing vertice and incident face will alway be 3
    int vertices [3];
    int incidentFaces [3];
    int nbFace;
    bool exist;

public:
    Face();
    Face(int a, int b, int c);

    void addFace(int i);
    void display();

    //get
    int getVertice(int i);
    void setVertice(int val, int pos);

    int getIncidentFace(int i);
    void setIncidentFace(int face, int pos);

    int getNextVertex(int vertex, bool local = true);

    // get position of vertex in tab incident face
    int getVerticeLocal(int vertex);
    
    void setExist(bool b);
    bool getExist();
};



class Mesh
{
    public:
    QVector<Vertice> verticesTab;
    QVector<Face> faces;
    QVector<int> deletedVertices;
    QVector<int> deletedFaces;

    int vertices_size;
    int faces_size;

// public:
    Mesh();

    void drawMesh();
    void drawMeshWireFrame();

    void display();

    void face_split(int face, Point p);

    void flip(int faceA, int faceB);

    void insert(Point p);

    bool collapse(int face, int p);

    bool simplify(int nb_faces);

    bool load_mesh(const std::string & filename);
    
    void clean();

    Iterator_on_faces faces_begin();
    Iterator_on_faces faces_past_the_end();

    Iterator_on_vertices vertices_begin();
    Iterator_on_vertices vertices_past_the_end();

    Circulator_on_faces incident_faces(Vertice & v);

    Circulator_on_vertices adjacent_vertices(Vertice & v);

    QVector<Face> & getFaces();
    QVector<Vertice> & getVertices();

};

#endif // MESH_H
