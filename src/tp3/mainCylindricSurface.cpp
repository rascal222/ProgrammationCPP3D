
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include <memory>


#include "../surfaces/CylindricSurface.hpp"
#include "../surfaces/BezierSurface.hpp"
#include "../surfaces/SurfacicSquare.hpp"
#include <GL/glut.h>



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

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=0.0f;
// XZ position of the camera
float x=0.0f,y=1.0f,z=5.0f;
int xOrigin = -1;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}



bool op=false;
std::shared_ptr<Surface> bs(nullptr);

GLvoid window_key(unsigned char key, int x, int y)
{
    switch(key)
    {
        case KEY_ESC:
            exit(1);
        case 9://TAB
            op=!op;
            break;
        case 43://+
            bs->setPointNumberForU(bs->getPointNumberForU()+1);
            break;
        case 45://-
            if(bs->getPointNumberForU()>2)
                bs->setPointNumberForU(bs->getPointNumberForU()-1);
            break;
        case 42://*
            bs->setPointNumberForV(bs->getPointNumberForV()+1);
            break;
        case 47:// /
            if(bs->getPointNumberForV()>2)
                bs->setPointNumberForV(bs->getPointNumberForV()-1);
            break;
        default:
            printf ("num touche %c %d\n",key,key);
    }
    glutPostRedisplay();
}

void init_scene()
{
    std::shared_ptr<Axis> axis(new Axis(Point::Origin,Vector(0,0,10)));

    std::vector<Point> vect;
    vect.push_back(Point::Origin);
    Point p(1,4,0);vect.push_back(p);
    Point p2(4,0,0);vect.push_back(p2);
    Point p3(8,-2,2);vect.push_back(p3);

    std::shared_ptr<BezierCurve> curve(new DeCasteljauBezierCurve(vect,100));

    bs.reset(new CylindricSurface(axis,curve));
    bs->setPointNumberForU(10);
    bs->setPointNumberForV(5);


}

void mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

void mouseMove(int x, int y) {

    // this will only be true when the left button is down
    if (xOrigin >= 0) {

        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;

        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}



int main(int argc, char **argv)
{
    // init GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");


    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(window_key);
    glutSpecialFunc(window_special_key);
    // here are the new entries
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    init_scene();
    // enter GLUT event processing cycle
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
void window_special_key ( int key, int x, int y ) {

    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
        case GLUT_KEY_UP : deltaMove = 0.5f; break;
        case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
        default:
            key;
    }
    //glutPostRedisplay(); // just update here....
}

GLvoid initGL()
{
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    renderScene();
    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2,-HEIGHT/2, HEIGHT/2, -2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


void computePos(float deltaMove) {

    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void renderScene()
{
    if (deltaMove)
        computePos(deltaMove);
    if (deltaAngle)
        computeDir(deltaAngle);
    // Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(	x, y, z,
            x+lx, y+ly,  z+lz,
            0.0f, 1.0f,  0.0f);


   bs->draw(op);


    glutSwapBuffers();
}
