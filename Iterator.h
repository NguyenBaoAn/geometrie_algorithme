#ifndef ITERATOR_H
#define ITERATOR_H

class Face;
class Mesh;
class Vertice;

class Iterator_on_faces
{
    int index;
    Mesh * mesh;

public:
    Iterator_on_faces();
    Iterator_on_faces(Mesh * m);
    Iterator_on_faces& operator++(int n);
    Iterator_on_faces& operator++();
    Face & operator*();
    bool operator!=(Iterator_on_faces it);

    void operator=(Iterator_on_faces it);

    // getter & setter
    int getIndex();
    void setIndex(int i);
    Mesh * getMesh();
};

class Iterator_on_vertices
{
    int index;
    Mesh * mesh;

public:
    Iterator_on_vertices();
    Iterator_on_vertices(Mesh * m);
    Iterator_on_vertices& operator++(int);
    Iterator_on_vertices& operator++();
    Vertice & operator*();
    bool operator!=(Iterator_on_vertices it);

    void operator=(Iterator_on_vertices it);

    int getIndex();
    void setIndex(int i);
    Mesh * getMesh();
};

class Circulator_on_faces {
    int incidentFace;
    int vertex;
    Mesh * mesh;

public:
    Circulator_on_faces();
    Circulator_on_faces(Mesh * m, int v);
    Circulator_on_faces& operator++(int);
    Circulator_on_faces& operator++();
    Face & operator*();
    bool operator!=(Circulator_on_faces it);

    void operator=(Circulator_on_faces it);

    int getIncidentFace();
    void setIncidentFace(int i);
    int getVertex();
    Mesh * getMesh();
};

class Circulator_on_vertices {
    int vertex;
    int adjacentVertex; // ATTENTION local to incident face
    int incidentFace;
    Mesh * mesh;

public:
    Circulator_on_vertices();
    Circulator_on_vertices(Mesh *m, int v);

    Circulator_on_vertices& operator++(int);
    Circulator_on_vertices& operator++();
    Vertice & operator*();
    bool operator!=(Circulator_on_vertices it);

    void operator=(Circulator_on_vertices it);

    int getIncidentFace();
    void setIncidentFace(int i);
    int getVertex();
    int getAdjacentVertex();
    Mesh * getMesh();
};

#endif // ITERATOR

