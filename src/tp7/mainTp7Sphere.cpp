//
// Created by sbeugnon on 30/03/15.
//
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


#include "../core/Point.hpp"
#include "../meshing/Mesh.hpp"
#include "../primitives/Cylinder.hpp"
#include "../primitives/Sphere.hpp"
#include "../glWrappers/GlCoreRendering.hpp"
#include "../glWrappers/EulerCamera.hpp"

#include "../meshing/Mesh.hpp"
#include "../meshing/OffManipulator.hpp"
#include "../primitives/Sphere.hpp"
#include "../meshing/AutoCenter.h"
#include "../meshing/FigureConverter.hpp"
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

//Camera variables
float deltaAngle1 = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;
EulerCamera eulerCamera(0, 0, 0, 5);
int xOrigin = -1;
int yOrigin = -1;

bool debug=false;

//Ortho variables
double left2 = -WIDTH/2;
double right2 = WIDTH/2;
double up = HEIGHT/2;
double down = -HEIGHT/2;
double near = -2.0;
double far = 100;
double meanX=0;
double meanY=0;
double meanZ=0;
double borderSize=WIDTH/2;


AutoCenter autoMeshCentering;


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



Mesh m;
prog_3D::Point p = prog_3D::Point::Origin;
prog_3D::Sphere s(20.0f,8,8,p);

GLvoid window_normal_key(unsigned char key, int x, int y)
{
    switch (key) {
        case KEY_ESC:
            exit(1); break;
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
            s.setMeridians(s.getMeridians()+1);
            m = FigureConverter::sphereToMesh(s);

            break;
        case 101: // e
            if(s.getMeridians()>1)
                s.setMeridians(s.getMeridians()-1);
            m = FigureConverter::sphereToMesh(s);

            break;
        case 114: // r
           break;
        case 111: // o
        case 108: // l
        case 107: // k
        case 109: // k (droite)
        case 113: // q
            s.setParalleles(s.getParalleles()+1);
            m = FigureConverter::sphereToMesh(s);
            break;
        case 115: // s
            if(s.getParalleles()>1)
            s.setParalleles(s.getParalleles()-1);
            m = FigureConverter::sphereToMesh(s);

            break;
        default:
            printf ("La touche %c (%d) n´est pas active.\n", key,key);
            break;
    }
    glutPostRedisplay();
}



Point pK(0, 0, 0);
void
initLightAndMaterial(void)
{
    static float ambient[] =
            {0.1, 0.1, 0.1, 1.0};
    static float diffuse[] =
            {0.5, 1.0, 1.0, 1.0};
    static float position[] =
            {(float)borderSize*autoMeshCentering.getFactor(),(float)borderSize*autoMeshCentering.getFactor(),(float)borderSize, 0.0};

    static float front_mat_shininess[] =
            {30.0};
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


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("TP7 - Sphere");
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

    m = FigureConverter::sphereToMesh(s);
    //init
    autoMeshCentering.setMesh(m);
    autoMeshCentering.computeBetterSize();
    autoMeshCentering.setFactor(2.0);
    borderSize=autoMeshCentering.getCachedBorderSize();
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



unsigned int* elements= nullptr;
float* points=nullptr;
float* normal=nullptr;

void renderScene()
{
    // Set the camera
    glColor3f(1.0f,1.0f,1.0f);

    for(unsigned long i=0;i<m.idTriangles.size();++i)
    {
        if(debug) {
            glDisable(GL_LIGHTING);
            prog_3D::wireframeTriangle
                    (
                            m.points.at((unsigned long) m.idTriangles.at(i).getPointId(0)),
                            m.points.at((unsigned long) m.idTriangles.at(i).getPointId(1)),
                            m.points.at((unsigned long) m.idTriangles.at(i).getPointId(2))
                    );
        } else
        {
            glEnable(GL_LIGHTING);
            prog_3D::fillTriangle
                    (
                            m.points.at((unsigned long) m.idTriangles.at(i).getPointId(0)),
                            m.points.at((unsigned long) m.idTriangles.at(i).getPointId(1)),
                            m.points.at((unsigned long) m.idTriangles.at(i).getPointId(2))
                    );
        }
    }

    glColor3f(1.0f,.0f,.0f);
    drawPoint(Point::Origin);
    glColor3f(.0f,1.0f,.0f);
    glColor3f(.0f,1.0f,1.0f);

    reper();

    glutSwapBuffers();
}
