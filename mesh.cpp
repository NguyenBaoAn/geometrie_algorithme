#include "mesh.h"
#include <iostream>
#include <fstream>

using namespace std;


int orientationTest(Point a, Point b, Point c) {
    QVector3D bc(c.x() - b.x(), c.y() - b.y(), c.z() - b.z());
    QVector3D ba(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());

    QVector3D normal = QVector3D::crossProduct(bc,ba);
    if (normal.z() > 0) return 1;
    else if (normal.z() < 0) return -1;
    else return 0;
}

int inTriangleTest(Point p, Point a, Point b, Point c) {
    int p1 = orientationTest(p, a, b);
    int p2 = orientationTest(p, b, c);
    int p3 = orientationTest(p, c, a);

    if ((p1 == 0) || (p2 == 0) || (p3 == 0)) return 0;
    else if ((p1 < 0) || (p2 < 0) || (p3 < 0)) return -1;
    else return 1;
}

double dist(Vertice v1, Vertice v2) {
    return sqrt(
            (v1.getCoordinate().x() - v2.getCoordinate().x()) * (v1.getCoordinate().x() - v2.getCoordinate().x())
            +(v1.getCoordinate().y() - v2.getCoordinate().y()) * (v1.getCoordinate().y() - v2.getCoordinate().y())
            +(v1.getCoordinate().z() - v2.getCoordinate().z()) * (v1.getCoordinate().z() - v2.getCoordinate().z()) );
}

bool Point::operator==(Point p) {
    return (_x == p.x()) && (_y == p.y()) && (_z == p.z());
}

void Point::display() {
    cout << '(' << _x << ',' << _y << ',' << _z << ')';
}


Vertice::Vertice()
{

}

Vertice::Vertice(float x, float y, float z, int incidentFace)
{
    _coordinate = Point(x, y, z);
    _incidentFace = incidentFace;
}

bool Vertice::operator==(Vertice v) {
    return ((_coordinate == v.getCoordinate()) && (_incidentFace == v.getIncidentFace()));
}

Point Vertice::getCoordinate() {
    return _coordinate;
}

void Vertice::setIncidentFace(int f) {
    _incidentFace = f;
}

int Vertice::getIncidentFace() {
    return _incidentFace;
}

Face::Face() {
    nbFace = 0;
    exist = true;
}

Face::Face(int a, int b, int c) {
    nbFace = 0;
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
    exist = true;
}

void Face::addFace(int i) {
    incidentFaces[nbFace] = i;
    nbFace++;

}

void Face::display() {
    cout << "======== Face information ======" << endl;
    cout << "vertice " << vertices[0] << " - " << vertices[1] << " - " << vertices[2] << endl;
    cout << "incidentFace ";
    for (int i = 0 ; i < nbFace; i++) {
        cout << incidentFaces[i] << " - ";
    } 
    cout << endl;

}

int Face::getVertice(int i) {
    return vertices[i];
}

void Face::setVertice(int val, int pos) {
    vertices[pos] = val;
}

int Face::getIncidentFace(int i) {
    return incidentFaces[i];
}

void Face::setIncidentFace(int face, int pos) {
    incidentFaces[pos] = face;
}


int Face::getNextVertex(int vertex, bool local) {
    // search vertex in local position of incident face to get the next
    int i;
    bool exist = false;
    for (i = 0; i < 3; i++) {
        if (vertices[i] == vertex) {
            exist = true;
            break;
        }
    }
    if (!exist) return -1;

    i = (i+1)%3;
    if (local) return i;
    else return vertices[i];
}

int Face::getVerticeLocal(int vertex) {

    // search vertex in local position of incident face to get the next
    int i;
    bool exist = false;
    for (i = 0; i < 3; i++) {
        if (vertices[i] == vertex) {
            exist = true;
            break;
        }
    }
    if (!exist) return -1;
    return i;
}

void Face::setExist(bool b) {
    exist = b;
}

bool Face::getExist() {
    return exist;
}


Mesh::Mesh()
{
    // 0 = tetrahedron
    // 1 = pyramide
    // 2 = 2D form to debug

    int forme = 2;

    if (forme == 0) {

        verticesTab.push_back(Vertice(-0.5, -0.5, -0.5, 0)); // 0
        verticesTab.push_back(Vertice(0.5,-0.5,-0.5, 2)); // 1
        verticesTab.push_back(Vertice(0,-0.5,0.5, 2)); // 2
        verticesTab.push_back(Vertice(0, 0.5,0, 3)); // 3

        vertices_size = 4;

        faces.push_back(Face(0,1,2)); // a 
        faces.push_back(Face(0,2,3)); // b
        faces.push_back(Face(2,1,3)); // c
        faces.push_back(Face(0,3,1)); // d

        faces_size = 4;

        // face a
        faces[0].addFace(2);
        faces[0].addFace(1);
        faces[0].addFace(3);

        //face b
        faces[1].addFace(2);
        faces[1].addFace(3);
        faces[1].addFace(0);

        //face c
        faces[2].addFace(3);
        faces[2].addFace(1);
        faces[2].addFace(0);

        //face d
        faces[3].addFace(2);
        faces[3].addFace(0);
        faces[3].addFace(1);

    }
    // TODO erreur sur l'orientation de la base?
    else if (forme == 1) {
        verticesTab.push_back(Vertice(-0.5,-0.5,-0.5, 0)); //0
        verticesTab.push_back(Vertice(-0.5,-0.5,0.5, 0)); //1
        verticesTab.push_back(Vertice(0.5,-0.5,0.5, 0)); //2
        verticesTab.push_back(Vertice(0.5,-0.5,-0.5, 1)); //3
        verticesTab.push_back(Vertice(0,0.5,0, 4)); //4 (top)

        vertices_size = 5;

        // base
        faces.push_back(Face(0,2,1)); // a 0
        faces.push_back(Face(2,0,3)); // b 1
        // cote
        faces.push_back(Face(0,1,4)); // c 2
        faces.push_back(Face(1,2,4)); // d 3
        faces.push_back(Face(2,3,4)); // e 4
        faces.push_back(Face(3,0,4)); // f 5

        faces_size = 6;

        // Face a
        faces[0].addFace(3);
        faces[0].addFace(2);
        faces[0].addFace(1);

        //face b
        faces[1].addFace(5);
        faces[1].addFace(4);
        faces[1].addFace(0);

        //face c
        faces[2].addFace(3);
        faces[2].addFace(5);
        faces[2].addFace(0);

        //face d
        faces[3].addFace(4);
        faces[3].addFace(2);
        faces[3].addFace(0);
    
        //face e
        faces[4].addFace(5);
        faces[4].addFace(3);
        faces[4].addFace(1);
        
        // face f
        faces[5].addFace(2);
        faces[5].addFace(4);
        faces[5].addFace(1);

    }

    else if (forme == 2) {
        verticesTab.push_back(Vertice( 0, 1, 0, 0)); // 0
        verticesTab.push_back(Vertice( 0, 0, 0, 0)); // 1
        verticesTab.push_back(Vertice( 1, 0, 0, 0)); // 2
        verticesTab.push_back(Vertice( 1, 1, 0, 1)); // 3

        // vertice immaginaire 4
        verticesTab.push_back(Vertice(0.5,0.5, -3, 2)); // 4
        vertices_size = 5;


        faces.push_back(Face(0,1,2)); // a 0
        faces.push_back(Face(2,3,0)); // b 1

        // imaginary faces 2+        
        faces.push_back(Face(0,4,1)); // c 2
        faces.push_back(Face(1,4,2)); // d 3
        faces.push_back(Face(2,4,3)); // e 4
        faces.push_back(Face(3,4,0)); // f 5
        
        faces_size = 6;

        // Face a
        faces[0].addFace(3);
        faces[0].addFace(1);
        faces[0].addFace(2);
        
        // Face b
        faces[1].addFace(5);
        faces[1].addFace(0);
        faces[1].addFace(4);
        
        // Face c
        faces[2].addFace(3);
        faces[2].addFace(0);
        faces[2].addFace(5);

        // Face d
        faces[3].addFace(4);
        faces[3].addFace(0);
        faces[3].addFace(2);

        // Face e
        faces[4].addFace(5);
        faces[4].addFace(1);
        faces[4].addFace(3);

        // Face f
        faces[5].addFace(2);
        faces[5].addFace(1);
        faces[5].addFace(4);
    }
}

// The following functions could be displaced into a module OpenGLDisplayMesh that would include Mesh
// Draw a vertex
void glVertexDraw(const Point & p) {
    glVertex3f(p.x(), p.y(), p.z());
}


// Only work if mesh have only polygone of 3 vertices (didnt check for more)
bool Mesh::load_mesh(const string & filename) {
    string txt;
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        cout << "erreur lecture de fichier mesh" << endl;
        return false;
    }

    double tmp;
    file >> vertices_size;
    file >> faces_size;
    file >> tmp;

    // add all vertices
    verticesTab.clear();
    for (int i = 0; i < vertices_size; i++) {
        double x,y,z;
        file >> x >> y >> z;
        verticesTab.push_back(Vertice(x,y,z, -1));
    }

    // first pair: segment opposite
    // second pair: current face (last vertice can be found)
    map<pair<int, int>, int> mesh_link;
    faces.clear(); 
    // face creation
    for (int i = 0; i < faces_size; i++) {
        int nb_vertice;
        int tab_vertice[3];

        file >> nb_vertice;
        for (int j = 0; j < nb_vertice; j++){
            file >> tab_vertice[j];

            if (verticesTab[tab_vertice[j]].getIncidentFace() == -1) {
                verticesTab[tab_vertice[j]].setIncidentFace(i);
            }
        }
        faces.push_back(Face(tab_vertice[0],tab_vertice[1],tab_vertice[2]));
        
        //own code hack
        for (int j = 0; j < 3; j++) {
            faces[i].addFace(-1);
        }

        for (int v = 0; v < nb_vertice; v++){
            pair<int, int> seg(tab_vertice[(v+1)%nb_vertice], tab_vertice[(v+2)%nb_vertice]);
            pair<int, int> seg_inv(tab_vertice[(v+2)%nb_vertice], tab_vertice[(v+1)%nb_vertice]);
            
            map<pair<int, int>, int>::iterator it;

            it = mesh_link.find(seg_inv);

            // if Opposite polygone exist case
            // else insert
            if (it != mesh_link.end())
            {
                int face_opposite = it->second;
                faces[i].setIncidentFace(face_opposite, v);
                
                // update for opposite too
                int pos = faces[face_opposite].getNextVertex(seg_inv.second, true);
                faces[face_opposite].setIncidentFace(i, pos);

                mesh_link.erase(it);
            } else {
                mesh_link.insert(pair<pair<int, int>, int>(seg, i));
            }
        }
    }

    cout << "lecture de fichier  réussi" << endl;
    return true;
}


void Mesh::face_split(int face, Point p) {
    verticesTab.push_back(Vertice(p.x(), p.y(), p.z(), 0));
    vertices_size++;
    // get vertex index
    int p1 = verticesTab.size() - 1;

    // keep a copy because face will be changed
    Face face_erased = faces[face];

    // index of new faces, the first face is the index of the old one
    int new_faces_index [3] = {face, faces.size(), faces.size() + 1};
    faces.push_back(Face(-1, -1, -1));
    faces.push_back(Face(-1, -1, -1));

    // split to 3 face
    for (int i = 0; i < 3; i++) {
        // cout << "==== creating face ==" << endl;
        int p0 = face_erased.getVertice(i);
        int p2 = face_erased.getVertice((i+2)%3);
        Face new_face(p0, p1, p2);

        int current_face = new_faces_index[i];
        


        // update incident for p0
        verticesTab[p0].setIncidentFace(current_face);

        // update opposite
        int opposite_face;
                    //next face     //start interval
        opposite_face = new_faces_index[(i+2)%3]; //get next*2 face in the interval of new faces
        new_face.addFace(opposite_face); // p0 

        opposite_face = face_erased.getIncidentFace((i+1)%3);
        new_face.addFace(opposite_face); // p1

        opposite_face = new_faces_index[(i+1)%3];
        new_face.addFace(opposite_face); //p2 
        
        faces[current_face] = new_face;
        
        // update opposite face for vertex adjacent to [p0,p2]
        // normaly always work because the rotation is counter-clock (circulator and face)
        Circulator_on_vertices cv_p0 = adjacent_vertices(verticesTab[p0]); // incident face of p0 must be set
        cv_p0++;
        int temp = cv_p0.getIncidentFace();

        // int temp = cv_p0.getIncidentFace();
        faces[temp].setIncidentFace(current_face ,faces[temp].getNextVertex(p2));
    }
    
    // the last face create is incident to new vertex;
    verticesTab[p1].setIncidentFace(faces.size() - 1);
    // erase 1 add 3 more face
    faces_size = faces.size();
}

void Mesh::flip(int faceA_, int faceB_) {
    // search for shared segment
    
    // indice of table vertex in face
    int segXY[2]; // face a
    int segYX[2]; // face b


    Face faceA = faces[faceA_];
    Face old_faceA = faces[faceA_];
    Face faceB = faces[faceB_];
    Face old_faceB = faces[faceB_];
    int i, j;
    int temp = 0;
    for (i = 0; i < 3 ; i++) {
        for (j = 0; j < 3; j++) {
            if (faceA.getVertice(i) == faceB.getVertice(j)) {
                segXY[temp] = faceA.getVertice(i);
                segYX[(temp+1)%2] = faceB.getVertice(j);
                temp++;
            }
        }
    }

    // fliping the edge XY

    // X of old_A = next to Y of old_B
    temp = old_faceB.getNextVertex(segXY[1], false);
    faceA.setVertice(temp, old_faceA.getVerticeLocal(segXY[0]));

    // Y of old_B = next to X of old_A
    temp = old_faceA.getNextVertex(segXY[0], false);
    faceB.setVertice(temp, old_faceB.getVerticeLocal(segXY[1]));

    // if nothing happen, XY wasn't "right"
    if (old_faceA.getVertice(0) == faceA.getVertice(0) && old_faceA.getVertice(1) == faceA.getVertice(1) && old_faceA.getVertice(2) == faceA.getVertice(2)) {
        int x = segXY[0];
        int y = segXY[1];
        segXY[0] = y;
        segXY[1] = x;

        temp = old_faceB.getNextVertex(segXY[1], false);
        faceA.setVertice(temp, old_faceA.getVerticeLocal(segXY[0]));

        temp = old_faceA.getNextVertex(segXY[0], false);
        faceB.setVertice(temp, old_faceB.getVerticeLocal(segXY[1]));
    }

    // update incident face
    int x_loc = faceB.getVerticeLocal(segXY[0]);
    int y_loc = faceA.getVerticeLocal(segXY[1]);

    verticesTab[segXY[0]].setIncidentFace(faceB_);
    verticesTab[segXY[1]].setIncidentFace(faceA_);

    // Doesn't need to update but it's useful for iterator later
    temp = faceA.getNextVertex(segXY[1], false);
    verticesTab[temp].setIncidentFace(faceA_);
    
    temp = faceB.getNextVertex(segXY[0], false);
    verticesTab[temp].setIncidentFace(faceB_);
    


    Circulator_on_vertices it;
    int f;
    // update opposite face A
    faceA.setIncidentFace(faceB_, y_loc); // c
    temp = old_faceA.getIncidentFace(old_faceA.getVerticeLocal(segXY[0]));
    faceA.setIncidentFace(temp, (y_loc + 1)%3); // d
    temp = old_faceB.getIncidentFace(old_faceB.getVerticeLocal(segXY[0]));
    faceA.setIncidentFace(temp, (y_loc + 2)%3);
    
    // end of modification for face A
    faces[faceA_] = faceA;


    // update opposite for neighbour face
    it = adjacent_vertices(verticesTab[faceA.getVertice( (y_loc + 1)%3 )]);
    it++;
    f = it.getIncidentFace();    
    i = (it.getAdjacentVertex() + 1) % 3;
    faces[f].setIncidentFace(faceA_, i);
        
    
    // Update opposite face B
    faceB.setIncidentFace(faceA_,x_loc); // a
    temp = old_faceB.getIncidentFace(old_faceB.getVerticeLocal(segXY[1]));
    faceB.setIncidentFace(temp , (x_loc+1)%3 ); // b
    temp = old_faceA.getIncidentFace(old_faceA.getVerticeLocal(segXY[1]));
    faceB.setIncidentFace(temp, (x_loc+2)%3 );

    // end of modification for face B
    faces[faceB_] = faceB;

    it = adjacent_vertices(verticesTab[faceB.getVertice( (x_loc+1)%3 )]);
    it++;
    f = it.getIncidentFace();
    i = (it.getAdjacentVertex() + 1) % 3;
    faces[f].setIncidentFace(faceB_, i);


    // update faceA
    // faces[faceA_] = faceA;
    // faces[faceB_] = faceB;
}


void Mesh::drawMesh() {

    int nb_col = 6;
    double col[nb_col][3] = {{1,0,0}, {0,1,0}, {0,0,1}, {1,1,0}, {0,1,1}, {1,0,1} };
    for(int i = 0; i < faces.size(); i++) {
        if (faces[i].getExist() == true) {
            glColor3d(col[i%nb_col][0], col[i%nb_col][1], col[i%nb_col][2]);

            glBegin(GL_TRIANGLES);
            glVertexDraw(verticesTab[faces[i].getVertice(0)].getCoordinate());
            glVertexDraw(verticesTab[faces[i].getVertice(1)].getCoordinate());
            glVertexDraw(verticesTab[faces[i].getVertice(2)].getCoordinate());

            glEnd();
        }
    }
}


//Example with a wireframe tedraedra
void Mesh::drawMeshWireFrame() {
    for(int i = 0; i < faces.size(); i++) {
        if (faces[i].getExist() == true) {
            glBegin(GL_LINE_STRIP);
                glVertexDraw(verticesTab[faces[i].getVertice(0)].getCoordinate());
                glVertexDraw(verticesTab[faces[i].getVertice(1)].getCoordinate());
            glEnd();
            glBegin(GL_LINE_STRIP);
                glVertexDraw(verticesTab[faces[i].getVertice(1)].getCoordinate());
                glVertexDraw(verticesTab[faces[i].getVertice(2)].getCoordinate());
            glEnd();
            glBegin(GL_LINE_STRIP);
                glVertexDraw(verticesTab[faces[i].getVertice(2)].getCoordinate());
                glVertexDraw(verticesTab[faces[i].getVertice(0)].getCoordinate());
            glEnd();
        }
    }

}

// no update for opposite face if exterior point
void Mesh::insert(Point p) {
    // boucle while avec flip? 
    // TODO Parcourir en fonction avec un iterateur de face sur le points infinie
    for (int f = 0; f < faces_size; f++) {
        Point a = verticesTab[faces[f].getVertice(0)].getCoordinate();
        Point b = verticesTab[faces[f].getVertice(1)].getCoordinate();
        Point c = verticesTab[faces[f].getVertice(2)].getCoordinate();

        int inTriangle = inTriangleTest(p, a , b, c);
        // Point situate in triangle
        if (inTriangle > 0) {
            face_split(f, p);
        }
        // exterior of triangle
        else if (inTriangle < 0) {
            // loop on edge
            verticesTab.push_back(Vertice(p.x(), p.y(), p.z(), -1));
            int p_index = vertices_size;
            vertices_size++;
            for (int i = 0; i < 3; i++) {
                if (orientationTest(p, verticesTab[faces[f].getVertice(i)].getCoordinate(), verticesTab[faces[f].getVertice((i+1)%3)].getCoordinate()) < 0) {
                    Face new_face(faces[f].getVertice((i+1)%3), faces[f].getVertice(i), p_index);
                    faces.push_back(new_face);
                    verticesTab[p_index].setIncidentFace(faces_size);
                    faces_size++;
                }
            }
        }
    }
}

// si les voisins des 2 sommet N,M sont les même, le collapse retourne faux
bool Mesh::collapse(int face, int p) {
    bool canCollapse = true;
    int tmp; // variable travail

    Circulator_on_faces cf;
    int faceA = face;
    int vertexA = p;

    int faceB = faces[faceA].getIncidentFace(faces[faceA].getVerticeLocal(p));
    // Le sommet N est situé avant le B (sens trigo)
    // Le sommet M est situé apres le B (sens trigo)
    int vertexB = -1;
    int vertexN = -1;
    int vertexM = -1;
    for (int i = 0; i < 3; i++) {
        if (faces[faceB].getIncidentFace(i) == faceA) {
            vertexB = faces[faceB].getVertice(i);
            vertexN = faces[faceB].getVertice((i+2)%3);
            
            vertexM = faces[faceB].getVertice((i+1)%3);
            tmp = faces[faceB].getIncidentFace((i+1)%3); // face incident valide pour le nouveau point C
            break;
        }
    }
    
    
    // Creation du point C (modification de N)
    int vertexC = vertexN;
    Point N = verticesTab[vertexN].getCoordinate();
    Point M = verticesTab[vertexM].getCoordinate();
    verticesTab[vertexC] = Vertice(0.5*N.x() + 0.5*M.x(), 0.5*N.y() + 0.5*M.y(), 0.5*N.z() + 0.5*M.z(), tmp);

    vector<int> verifyUnique;

    vector<int> sideFaceM;
    // cherche les face cote M
    verticesTab[vertexM].setIncidentFace(faceB);
    cf = incident_faces(verticesTab[vertexM]);
    cf++;    
    while (cf.getIncidentFace() != faceA) {
        sideFaceM.push_back(cf.getIncidentFace());
        
        // permet de verifier que tout les voisin de M est different des voisin de N
        // peut optimiser
        tmp = cf.getVertex();
        if (tmp != vertexA && tmp != vertexB && tmp != vertexA 
            && tmp != vertexN && tmp != vertexM)
        {
            verifyUnique.push_back(tmp);
        }
        cf++;
    }

    vector<int> sideFaceN;
    // cherche les face cote N
    verticesTab[vertexN].setIncidentFace(faceA);
    cf = incident_faces(verticesTab[vertexN]);
    cf++;
    while (cf.getIncidentFace() != faceB) {
        sideFaceN.push_back(cf.getIncidentFace());

        // verifier que tout les voisin de M est different des voisin de N
        // peut optimiser
        int tmp = cf.getVertex();
        if (tmp != vertexA && tmp != vertexB && tmp != vertexA 
            && tmp != vertexN && tmp != vertexM)
        {
            if (find(verifyUnique.begin(), verifyUnique.end(), tmp) != verifyUnique.end()) canCollapse = false;
        }
        cf++;
    }

    // verification que les voisins des 2 sommet N,M sont different
    if (!canCollapse) {
        cout << "cannot collapse, same neighborhood" << endl;
        return false;
    }

    // mise a jour des faces opposée
    int pos;
    pos = faces[sideFaceN.back()].getNextVertex(vertexN);

    faces[sideFaceN.back()].setIncidentFace(sideFaceM.front(), pos);

    pos = faces[sideFaceM.front()].getNextVertex(vertexB);
    faces[sideFaceM.front()].setIncidentFace(sideFaceN.back(), pos);

    pos = faces[sideFaceM.back()].getNextVertex(vertexM);
    faces[sideFaceM.back()].setIncidentFace(sideFaceN.front(), pos);

    pos = faces[sideFaceN.front()].getNextVertex(vertexA);
    faces[sideFaceN.front()].setIncidentFace(sideFaceM.back(), pos);

    // fusion du nouveau sommet avec M
    for (int i = 0; i < sideFaceM.size(); i++) {
        pos = faces[sideFaceM[i]].getVerticeLocal(vertexM);
        faces[sideFaceM[i]].setVertice(vertexC, pos);
    }
    // random incident face N pour au cas ou ancien incident face sur face supprimer
    verticesTab[vertexC].setIncidentFace(sideFaceN.back());
    
    // suppression fausse pour l'affichages
    faces[faceA].setExist(false);
    faces[faceB].setExist(false);
    deletedFaces.push_back(faceA);
    deletedFaces.push_back(faceB);
    deletedVertices.push_back(vertexM);

    return true;
}

bool order_toSimplify(tuple<double, int, int> n1, tuple<double, int, int> n2) {
    return get<0>(n1) < get<0>(n2);
}

// return false if nb_faces is bigger than number face of mesh
// cannot always collapse so we try to simplify to nb_faces. 
bool Mesh::simplify(int nb_faces) {
    // length segment, face, opposite vertex of segment
    vector<tuple<double, int, int>> toSimplify;

    if (nb_faces > faces.size()) {
        cout << "le nombre de face voulu est plus grand que le nombre de face existant" << endl;
        return false;
    } 
    int nb = (faces.size() - nb_faces)/2;
    for (int n = 0; n < nb; n++) {
        
        // sort all segment
        for (int i = 0; i < faces.size(); i++) {
            if (faces[i].getExist()) {
                for (int j = 0; j < 3; j++) {
                    double l = dist(verticesTab[faces[i].getVertice((j+1)%3)], verticesTab[faces[i].getVertice((j+2)%3)]);
                    toSimplify.push_back(make_tuple(l, i, j));
                }
            }
        }
        sort(toSimplify.begin(), toSimplify.end(), order_toSimplify);



        // collapse on a random side(trigo side)
        int f = get<1>(toSimplify[n]);
        int v = faces[f].getVertice((get<2>(toSimplify[n]) + 1)%3);
        bool sucess = collapse(f, v);
        // if can't not collapse, try the other side
        if (!sucess) {
            faces[f].getVertice((get<2>(toSimplify[n]) + 2)%3);
            sucess = collapse(f, v);
        }

        toSimplify.clear();
    }
    return true;
}

void Mesh::clean() {
    // nettoyage des faces
    std::sort(deletedVertices.begin(), deletedVertices.end());
    std::sort(deletedFaces.begin(), deletedFaces.end());


    QVector<int>::iterator low;

    
    for (int i =0; i < faces.size(); i++) {
        for (int j = 0; j < 3; j++) {
            // valeur offset est 0 si le sommet n'a pas besoin de decalage

            //sommet des faces        
            low = std::lower_bound(deletedVertices.begin(), deletedVertices.end(), faces[i].getVertice(j));            
            int offset = low-deletedVertices.begin();
            faces[i].setVertice(faces[i].getVertice(j) - offset, j);

            //faces opposer
            low = std::lower_bound(deletedFaces.begin(), deletedFaces.end(), faces[i].getIncidentFace(j));
            offset = low-deletedFaces.begin();
            faces[i].setIncidentFace(faces[i].getIncidentFace(j) - offset, j);

        }
    }

    

    // nettoyage des vertices
    for (int i =0; i < verticesTab.size(); i++) {
        // valeur offset est 0 si le sommet n'a pas besoin de decalage
        
        // faces incident
        low = std::lower_bound(deletedFaces.begin(), deletedFaces.end(), verticesTab[i].getIncidentFace());
        int offset = low-deletedFaces.begin();
        // valeur est 0 si le sommet n'a pas besoin de decalage
        verticesTab[i].setIncidentFace(verticesTab[i].getIncidentFace() - offset);

        
    }

    // re ordonner le tableau
    for (int i = deletedFaces.size() - 1; i >= 0; i--) {
        faces.erase(faces.begin() + deletedFaces[i]);
    }

    for (int i = deletedVertices.size()-1; i >= 0; i--) {
        verticesTab.erase(verticesTab.begin() + deletedVertices[i]);
    }
    faces_size = faces.size();
    vertices_size = verticesTab.size();
}

QVector<Face> & Mesh::getFaces() {
    return faces;
}

QVector<Vertice> & Mesh::getVertices() {
    return verticesTab;
}


// Iterator
Iterator_on_faces Mesh::faces_begin() {
    return Iterator_on_faces(this);
}

Iterator_on_faces Mesh::faces_past_the_end() {
    Iterator_on_faces it(this);
    it.setIndex(faces_size);
    return it;
}


Iterator_on_vertices Mesh::vertices_begin() {
    return Iterator_on_vertices(this);
}

Iterator_on_vertices Mesh::vertices_past_the_end() {
    Iterator_on_vertices it(this);
    it.setIndex(vertices_size);
    return it;
}

Circulator_on_faces Mesh::incident_faces(Vertice & v) {
    // search vertex id;
    for (int i = 0; i < vertices_size; i++) {
        if (verticesTab[i] == v) return Circulator_on_faces(this, i);
    }
    return Circulator_on_faces();
}   

Circulator_on_vertices Mesh::adjacent_vertices(Vertice & v) {
    for (int i = 0; i < vertices_size; i++) {
        if (verticesTab[i] == v) return Circulator_on_vertices(this, i);
    }
    return Circulator_on_vertices();
} 

void Mesh::display() {
    for (int i = 0; i < faces.size(); i++) {
        cout << " =============== "<< " face " << i << " ==============" << endl;
        faces[i].display();
    }
    cout << endl;
}

