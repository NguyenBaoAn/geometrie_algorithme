// #include "iterator.h"
#include "mesh.h"
#include <cstddef>
#include <iostream>

using namespace std;

Iterator_on_faces::Iterator_on_faces() {
    index = -1;
    mesh = nullptr;
}

Iterator_on_faces::Iterator_on_faces(Mesh * m) {
    index = 0;
    mesh = m;
}

Iterator_on_faces& Iterator_on_faces::operator++(int) {
    index++;
    return *this;
}

Iterator_on_faces& Iterator_on_faces::operator++() {
    return (*this)++;
}

Face & Iterator_on_faces::operator*() {
    return mesh->getFaces()[index];
}

bool Iterator_on_faces::operator!=(Iterator_on_faces it) {
    bool verif = false;
    verif = verif || (index != it.getIndex()); 
    verif = verif || (mesh != it.getMesh());
    
    return verif;
}

void Iterator_on_faces::operator=(Iterator_on_faces it) {
    index = it.getIndex();
    mesh = it.getMesh();
    
    // return *this;
}

int Iterator_on_faces::getIndex() {
    return index;
}
Mesh * Iterator_on_faces::getMesh() {
    return mesh;
}

void Iterator_on_faces::setIndex(int i) {
    index = i;
}

/////////////////////////////////////////////////////////////

Iterator_on_vertices::Iterator_on_vertices() {
    index = -1;
    mesh = nullptr;
}

Iterator_on_vertices::Iterator_on_vertices(Mesh * m) {
    index = 0;
    mesh = m;
}

Iterator_on_vertices& Iterator_on_vertices::operator++(int) {
    index++;
    return *this;
}

Iterator_on_vertices& Iterator_on_vertices::operator++() {
    return (*this)++;
}

Vertice & Iterator_on_vertices::operator*() {
    return mesh->getVertices()[index];
}

bool Iterator_on_vertices::operator!=(Iterator_on_vertices it) {
    bool verif = false;
    verif = verif || (index != it.getIndex()); 
    verif = verif || (mesh != it.getMesh());
    
    return verif;
}

void Iterator_on_vertices::operator=(Iterator_on_vertices it) {
    index = it.getIndex();
    mesh = it.getMesh();
    
    // return *this;
}

int Iterator_on_vertices::getIndex() {
    return index;
}
Mesh * Iterator_on_vertices::getMesh() {
    return mesh;
}

void Iterator_on_vertices::setIndex(int i) {
    index = i;
}

/////////////////////////////////////////////////////////////

Circulator_on_faces::Circulator_on_faces() {
    mesh = nullptr;
    vertex = -1;
    incidentFace = -1;
}
Circulator_on_faces::Circulator_on_faces(Mesh * m, int v) {
    mesh = m;
    vertex = v;
    incidentFace = m->getVertices()[v].getIncidentFace();
}

// Keep to debug
// Circulator_on_faces& Circulator_on_faces::operator++(int) {
//     // this code can be in a function of mesh -> getOppositeOfVertex;
//     int size = 3; // number of vertex in face
//     // search vertex in local position of incident face to get the next
//     int i;
//     for (i = 0; i < size; i++) {
//         if (mesh->getFaces()[incidentFace].getVertice(i) == vertex) {
//             // cout << "mitsuketa" << endl;
//             break;
//         }
//     }
//     i = (i+1)%size;
//     // cout << mesh->getFaces()[incidentFace].getVertice(i) << " desu" << endl;
//     incidentFace = mesh->getFaces()[incidentFace].getIncidentFace(i); 
//     // cout << "next incidentFace is " << incidentFace << endl;
//     return *this;
// }

Circulator_on_faces& Circulator_on_faces::operator++(int) {
    int v = mesh->getFaces()[incidentFace].getNextVertex(vertex);
    incidentFace = mesh->getFaces()[incidentFace].getIncidentFace(v); 
    return *this;
}

Circulator_on_faces& Circulator_on_faces::operator++() {
    return (*this)++;
}

Face & Circulator_on_faces::operator*() {
    return mesh->getFaces()[incidentFace];
}

bool Circulator_on_faces::operator!=(Circulator_on_faces it) {
    bool verif = false;
    verif = verif || (incidentFace != it.getIncidentFace()); 
    verif = verif || (mesh != it.getMesh());
    verif = verif || (vertex != it.getVertex());

    return verif;
}

void Circulator_on_faces::operator=(Circulator_on_faces it) {
    mesh = it.getMesh();
    vertex = it.getVertex();
    incidentFace = it.getIncidentFace();
}

Mesh * Circulator_on_faces::getMesh() {
    return mesh;
}

int Circulator_on_faces::getIncidentFace() {
    return incidentFace;
}
void Circulator_on_faces::setIncidentFace(int i) {
    incidentFace = i;
}
int Circulator_on_faces::getVertex() {
    return vertex;
}

/////////////////////////////////////////////////////////////

Circulator_on_vertices::Circulator_on_vertices() {
    vertex = -1;
    adjacentVertex = -1;
    incidentFace = -1;
    mesh = nullptr;
}

Circulator_on_vertices::Circulator_on_vertices(Mesh *m, int v) {
    mesh = m;
    vertex = v;
    incidentFace = m->getVertices()[v].getIncidentFace();
    adjacentVertex = m->getFaces()[incidentFace].getNextVertex(v);
}

Circulator_on_vertices& Circulator_on_vertices::operator++(int) {
    
    incidentFace = mesh->getFaces()[incidentFace].getIncidentFace(adjacentVertex);
    adjacentVertex = mesh->getFaces()[incidentFace].getNextVertex(vertex);
    // cout << "face : " << incidentFace << endl;
    // cout << "adj vertex : " << mesh->getFaces()[incidentFace].getVertice(adjacentVertex) << endl;
    return *this;
}
Circulator_on_vertices& Circulator_on_vertices::operator++() {
    return (*this)++;
}


Vertice & Circulator_on_vertices::operator*() {
    // get global value
    int v = mesh->getFaces()[incidentFace].getVertice(adjacentVertex);
    
    return mesh->getVertices()[v];
}

bool Circulator_on_vertices::operator!=(Circulator_on_vertices it) {
    bool verif = false;
    verif = verif || (adjacentVertex != it.getAdjacentVertex()); 
    verif = verif || (incidentFace != it.getIncidentFace()); 
    verif = verif || (mesh != it.getMesh());
    verif = verif || (vertex != it.getVertex());

    return verif;
}

void Circulator_on_vertices::operator=(Circulator_on_vertices it) {
    mesh = it.getMesh();
    vertex = it.getVertex();
    adjacentVertex = it.getAdjacentVertex();
    incidentFace = it.getIncidentFace();
}

Mesh * Circulator_on_vertices::getMesh() {
    return mesh;
}

int Circulator_on_vertices::getAdjacentVertex() {
    return adjacentVertex;
}

int Circulator_on_vertices::getVertex() {
    return vertex;
}

int Circulator_on_vertices::getIncidentFace() {
    return incidentFace;
}
void Circulator_on_vertices::setIncidentFace(int i) {
    incidentFace = i;
}