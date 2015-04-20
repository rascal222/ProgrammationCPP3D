//
// Created by beugnon on 16/04/15.
//

//
// Created by beugnon on 19/04/15.
//

#include <random>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GL/glext.h>
#include <GLES3/gl3ext.h>

#include "../glWrappers/GlCoreRendering.hpp"

#include "../glWrappers/EulerCamera.hpp"

#include "../meshing/Mesh.hpp"
#include "../meshing/OffManipulator.hpp"
#include "../primitives/Sphere.hpp"
#include "../meshing/AutoCenter.h"
#include "../meshing/TopoMesh.h"
#include "../primitives/Grid.h"
#include "../primitives/GridDecimer.h"
#include <string>
// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define KEY_ESC 27
using namespace prog_3D;
using namespace std;
// Entêtes de fonctions
void init_scene();
void renderScene();
GLvoid initGL();
GLvoid window_display();
GLvoid changeSize(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_special_key(int key, int x, int y);

GLuint createVBO(const void* data, int dataSize, GLenum target=GL_ARRAY_BUFFER_ARB, GLenum usage=GL_STATIC_DRAW_ARB);
void deleteVBO(const GLuint vboId){glDeleteBuffers(1, &vboId);}
void cleanSharedMem();



//Camera variables
float deltaAngle1 = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;
EulerCamera eulerCamera(0, 0, 0, 5);
int xOrigin = -1;
int yOrigin = -1;


bool debug = false;
bool showNormal = false;
bool showTest = false;
bool showOneFace = false;
bool showActive = false;
bool vboUsed = true;


GLubyte**color3i = nullptr;
GLfloat* vertices = nullptr;
GLfloat* normals = nullptr;
GLfloat* colors = nullptr;
GLuint* triangles = nullptr;


GLuint vboId_1 = 0;                   // ID of VBO for vertex arrays
GLuint vboId_normal = 0;
GLuint vboId_color = 0;
GLuint vboId_indices = 0;


bool first = true;
unsigned long cursor = 0;

Point pK(0, 0, 0);
Mesh* m;
std::string file("cube.off");

Grid autoMeshCentering;
TopoMesh* tm = nullptr;
Mesh original;

void mouseButton(int button, int state, int x, int y) {
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON)
    {
        // when the button is released
        if (state == GLUT_DOWN) {// state = GLUT_DOWN
            xOrigin = x;//Click position
            yOrigin = y;
        }
        else {
            yOrigin = -1;
            xOrigin = -1;
            deltaAngle1 = 0.0f;
            deltaAngle2 = 0.0f;
        }

    }
    else if(button == 3 && state ==1)//DEZOOM
        eulerCamera.computeEvent(0.05f,0,0,0);
    else if(button ==4 && state == 1)//ZOOM
        eulerCamera.computeEvent(-0.05f,0.f,0.f,0.f);
    glutPostRedisplay();
}

void mouseMove(int x, int y) {
    // this will only be true when the left button is down
    if (xOrigin >= 0) { //Click
        // update deltaAngle
        deltaAngle1 = (x - xOrigin) * 0.001f;
    }
    else
        deltaAngle1=0.0f;

    if(yOrigin >= 0)
    {
        deltaAngle2 = (y - yOrigin) * 0.001f;
    }
    else
        deltaAngle2 = 0.0f;

    glutPostRedisplay();
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle1 = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaAngle2 = 0.0f;break;
    }
    //glutPostRedisplay();
}


void window_special_key(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT :
            //eulerCamera.setXTarget(eulerCamera.getXtarget()-0.01f);
            break;
        case GLUT_KEY_RIGHT :
            //eulerCamera.setXTarget(eulerCamera.getXtarget()+0.01f);
            break;
        case GLUT_KEY_UP :
            //eulerCamera.setZTarget(eulerCamera.getZtarget()+0.01f);
            break;
        case GLUT_KEY_DOWN :
            // eulerCamera.setZTarget(eulerCamera.getZtarget()-0.01f);
            break;
    }
    //glutPostRedisplay(); // just update here....
}

void reduceMesh(int id) {
    if(id==0)
        autoMeshCentering.setNb(autoMeshCentering.getNb()+1);
    else
        if(autoMeshCentering.getNb()>0)
            autoMeshCentering.setNb(autoMeshCentering.getNb()-1);

    GridDecimer gd(&autoMeshCentering,&original);
    m = gd.reduceMesh();
    cleanSharedMem();
    first=true;
    delete vertices;
    delete normals;
    delete triangles;
    delete tm;
    tm = new TopoMesh(*m);
}



GLvoid window_normal_key(unsigned char key, int x, int y)
{
    switch (key) {
        case KEY_ESC:
            exit(1);
        case 43:
            autoMeshCentering.setFactor(autoMeshCentering.getFactor()+0.5);
            break; // +
        case 45:
            autoMeshCentering.setFactor(autoMeshCentering.getFactor()-0.5);
            break; // --
        case 97: // a
            debug = !debug;
            break;
        case 122: // z
            //TODO REDUCE MESH
           reduceMesh(0);
            break;
        case 101: // e
            showActive= !showActive;
            break;
        case 178://²
            vboUsed= !vboUsed;
            std::cout <<"show vbo : " << ((vboUsed)?"On":"Off")<<std::endl;
            break;
        case 114: // r
            showNormal= !showNormal;
            std::cout <<"show Normal : " << ((showNormal)?"On":"Off")<<std::endl;
            break;
        case 111: // o
            cursor++;
            break;
        case 108: // l
            if(cursor>0)
                cursor--;
            break;
        case 107: // k
            showTest = !showTest;
            break;
        case 109: // m (droite)
            break;
        case 113: // q
            break;
        case 115: // s
            reduceMesh(1);
            break;
        default:
            printf ("La touche %c (%d) n´est pas active.\n", key,key);
    }
    glutPostRedisplay();
}


void
initLightAndMaterial(void)
{
    static float ambient[] =
            {0.1, 0.1, 0.1, 1.0};
    static float diffuse[] =
            {0.5, 1.0, 1.0, 1.0};
    static float position[] =
            {(float)autoMeshCentering.getCachedBorderSize(),(float)autoMeshCentering.getCachedBorderSize(),(float)autoMeshCentering.getCachedBorderSize(), 0.0};

    static float front_mat_shininess[] =
            {60.0};
    static float front_mat_specular[] =
            {0.2, 0.2, 0.2, 1.0};
    static float front_mat_diffuse[] =
            {0.5, 0.5, 0.28, 1.0};
    static float back_mat_shininess[] =
            {60.0};
    static float back_mat_specular[] =
            {0.5, 0.5, 0.2, 1.0};
    static float back_mat_diffuse[] =
            {1.0, 0.2, 0.2, 1.0};

    static float lmodel_ambient[] =
            {1.0, 1.0, 1.0, 1.0};

    static float lmodel_twoside[] =
            {GL_TRUE};


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_SHININESS, front_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, front_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
    glMaterialfv(GL_BACK, GL_SHININESS, back_mat_shininess);
    glMaterialfv(GL_BACK, GL_SPECULAR, back_mat_specular);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

    glShadeModel(GL_SMOOTH);
}


int main(int argc, char **argv)
{
    // init GLUT and create window
    if(argc==2){
        file.clear();
        file = std::string(argv[1]);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("TP9-Decimation");
    initGL();
    //initLightAndMaterial();
    init_scene();

    // register callbacks
    glutDisplayFunc(window_display);
    glutReshapeFunc(changeSize);
    glutIdleFunc(window_display);
    glutKeyboardFunc(window_normal_key);
    glutSpecialFunc(window_special_key);
    // here are the new entries
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);
    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    // OpenGL init

    glutMainLoop();

    return 1;
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    double ratio = w * 1.0 / h;
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset Matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    // Set the correct perspective.
    gluPerspective(45,ratio,1,100);
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

GLvoid initGL()
{
    glClearColor(RED, GREEN, BLUE, ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    initLightAndMaterial();
}



void init_scene()
{
    OffManipulator off;
    original = off.read(file);


    //init
    autoMeshCentering.setMesh(original);
    autoMeshCentering.setFactor(2.0);
    autoMeshCentering.computeBetterSize();

    GridDecimer gd(&autoMeshCentering,&original);
    m = gd.reduceMesh();
    tm = new TopoMesh(*m);
    std::cout <<"points:"<< m->points.size() << std::endl;
    std::cout <<"triangles:"<< m->idTriangles.size()<<std::endl;
    eulerCamera.setXTarget(autoMeshCentering.getCenter().getX());
    eulerCamera.setYTarget(autoMeshCentering.getCenter().getY());
    eulerCamera.setZTarget(autoMeshCentering.getCenter().getZ());
    eulerCamera.setYViewport(1);
    eulerCamera.setDist(autoMeshCentering.getCachedBorderSize()/2.0);
}


GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Setting projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //TODO LINK THIS IN FUNCTION OF MESH
    autoMeshCentering.placeOrtho();
    //Setting Model viewer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    eulerCamera.computeEvent(deltaMove,0.0f,deltaAngle1,deltaAngle2);
    eulerCamera.place();
    renderScene();
    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

}


GLvoid window_key(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}


void reper() {
    //glDisable(GL_LIGHTING);
    drawPoint(Point::Origin);
    Point p;
    p = p.translate(Vector::UP);//Y
    glColor3d(1.0, 0, 0);
    drawLine(Point::Origin, p);
    p = p.translate(Vector::DOWN);//Y
    p = p.translate(Vector::RIGHT);//X
    glColor3d(0, 1.0, 0);
    drawLine(Point::Origin, p);

    p = p.translate(Vector::LEFT);
    p = p.translate(Vector::FORWARD);
    glColor3d(0, 0, 1);
    drawLine(Point::Origin, p);
}


void fillTriangle(TopoFace* topoFace)
{
    std::vector<TopoPoint*> v = topoFace->getVertices();
    prog_3D::Vector n = topoFace->getNormal();
    prog_3D::fillTriangle(
            *v.at(0),
            *v.at(1),
            *v.at(2),n);
}

void drawEdge(TopoEdge* edge)
{
    drawLine(*edge->getPoints().at(0),*edge->getPoints().at(1));
}

void drawMeshByVBO()
{

    if (!debug) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    }
    if(first)
    {
        first = false;
        //Compute vertices
        std::cout<<"init vbo"<<std::endl;
        vertices = m->getPointVector();
        normals = tm->getPointNormals();
        triangles = m->getIdVector();
        std::cout<<"end global init"<<std::endl;


        std::cout<<"before vbo gen"<<std::endl;

        glGenBuffers(1, &vboId_1);
        glGenBuffers(1, &vboId_indices);
//        glGenBuffers(1, &vboId_color);
        int bufferSize=0;
        std::cout<<"before vbo bind"<<std::endl;

        glBindBuffer(GL_ARRAY_BUFFER, vboId_1);
        glBufferData(GL_ARRAY_BUFFER, 2*sizeof(float)*3* m->points.size(), 0, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 3*sizeof(float)* m->points.size(), vertices);
        glBufferSubData(GL_ARRAY_BUFFER, 3*sizeof(float)* m->points.size(), 3*sizeof(float)* m->points.size(), normals);
//        glBufferSubData(GL_ARRAY_BUFFER, 2*3*sizeof(float)*tm->getPoints().size(), 3*sizeof(float)*tm->getPoints().size(), colors);
        std::cout<<"after vbo bind array"<<std::endl;

        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
        std::cout << "Vertex and Normal Array in VBO: " << bufferSize << " bytes ("<< m->points.size()*sizeof(float)*3*2 <<")\n";
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId_indices);                    // activate vbo id to use
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(unsigned int)*m->idTriangles.size(), triangles, GL_STATIC_DRAW); // upload data to video card
        bufferSize=0;
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
        std::cout << "Indice Array in VBO: " << bufferSize << " bytes ("<< m->idTriangles.size()*sizeof(unsigned int)*3 <<")\n";
        if(3*sizeof(unsigned int)*m->idTriangles.size() != bufferSize)
        {
            glDeleteBuffers(1, &vboId_indices);
            glDeleteBuffers(1, &vboId_1);
            vboId_indices = 0;
            std::cout << bufferSize << std::endl;
            std::cout << "[createVBO()] Data size is mismatch with input array\n";
            exit(120);
        }
    }


    glBindBuffer(GL_ARRAY_BUFFER, vboId_1);
    glNormalPointer(GL_FLOAT,0,(void*)(3*sizeof(float)*m->points.size()));
//    glColorPointer(3,GL_FLOAT,0,(void*)(2*3*sizeof(float)*tm->getPoints().size()));
    glVertexPointer(3, GL_FLOAT, 0,0);
    //glBindBuffer(GL_ARRAY_BUFFER,vboId_color);
    //glColorPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId_indices);
    glIndexPointer(GL_UNSIGNED_INT,0,0);

    // enable vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements( GL_TRIANGLES,3*m->idTriangles.size(), GL_UNSIGNED_INT, (GLuint*)0+0 );
    //for(int i=0;i<3*m.idTriangles.size();++i)
    //  glDrawElements( GL_TRIANGLES,2, GL_UNSIGNED_INT, (GLuint*)0+i );
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
//    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void fillTriangle(Mesh& m, IdTriangle& triangle){
    prog_3D::fillTriangle(m.points.at(triangle.getPointId(0)),m.points.at(triangle.getPointId(1)),m.points.at(triangle.getPointId(2)));
}

void drawMeshByClassicMethod()
{
    if(!showTest) {
        for (unsigned long i = 0; i < m->idTriangles.size(); ++i) {
            if (!debug) {

                fillTriangle(*m,m->idTriangles.at(i));
            }
            else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                fillTriangle(*m,m->idTriangles.at(i));
            }

        }
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    if(showNormal)
    {
        glColor3f(1.0f,.0f,.0f);
        for(unsigned int i=0;i<tm->getFaces().size();++i)
        {
            drawLine(tm->getFaces().at(i)->getCenter(),tm->getFaces().at(i)->getNormal());
        }
    }

}

void drawMesh(Mesh* mesh) {
    for (unsigned long i = 0; i < mesh->idTriangles.size(); ++i) {
        if (!debug) {

            fillTriangle(*mesh,mesh->idTriangles.at(i));
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            fillTriangle(*mesh,mesh->idTriangles.at(i));
        }

    }
}

void renderScene() {

    glDisable(GL_LIGHTING);
    // Set the camera
    glColor3f(1.0f,1.0f,1.0f);
    if(vboUsed)
        drawMeshByVBO();
    else
        drawMeshByClassicMethod();


    if(showActive) {
        drawMesh(&original);
    }


    glColor3f(1.0f,1.0f,1.0f);
    if(showTest)
        autoMeshCentering.draw();
    reper();

    glutSwapBuffers();
}

void cleanSharedMem()
{
    deleteVBO(vboId_1);
    deleteVBO(vboId_indices);
}