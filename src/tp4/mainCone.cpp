#include <GL/gl.h>
#include <GL/glut.h>
#include "../glWrappers/EulerCamera.hpp"
#include "../primitives/Cone.hpp"
#include "../primitives/Cylinder.hpp"
#include <cmath>
#include <iostream>

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

int LightPos[4] = {0, 4, 3, 1};
int MatSpec[4] = {1, 1, 1, 1};
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle1 = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;
EulerCamera eulerCamera(0, 0, 0, 5);
int xOrigin = -1;
int yOrigin = -1;

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
    else if(button =4 && state == 1)//ZOOM
        eulerCamera.computeEvent(-0.05f,0.f,0.f,0.f);
    //glutPostRedisplay();
}

void mouseMove(int x, int y) {
    // this will only be true when the left button is down
    if (xOrigin >= 0) { //Click
        // update deltaAngle
        deltaAngle1 = (x - xOrigin) * 0.01f;
    }
    else
        deltaAngle1=0.0f;

    if(yOrigin >= 0)
    {
        deltaAngle2 = (y - yOrigin) * 0.01f;
    }
    else
        deltaAngle2 = 0.0f;

    //glutPostRedisplay();
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

int main(int argc, char **argv) {
    // init GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    initGL();
    init_scene();
    // register callbacks
    glutDisplayFunc(window_display);
    glutReshapeFunc(changeSize);
    glutIdleFunc(window_display);
    //glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(window_special_key);
    // here are the new entries
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);


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
    gluPerspective(45, ratio, 1, 100);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void window_special_key(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT :
            eulerCamera.setXTarget(eulerCamera.getXtarget()-0.01f);
            break;
        case GLUT_KEY_RIGHT :
            eulerCamera.setXTarget(eulerCamera.getXtarget()+0.01f);
            break;
        case GLUT_KEY_UP :
            eulerCamera.setZTarget(eulerCamera.getZtarget()+0.01f);
            break;
        case GLUT_KEY_DOWN :
            eulerCamera.setZTarget(eulerCamera.getZtarget()-0.01f);
            break;
    }
    glutPostRedisplay(); // just update here....
}


GLvoid initGL() {
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

void init_scene() {
}


GLvoid window_display() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    eulerCamera.computeEvent(deltaMove,0.0f,deltaAngle1,deltaAngle2);
    eulerCamera.place();
    renderScene();
    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


GLvoid window_key(unsigned char key, int x, int y) {
    glutPostRedisplay();
}



void renderScene()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    LightPos[0] = 0;
    LightPos[1] = 0;
    LightPos[2] = 0;
    glLightiv(GL_LIGHT0, GL_POSITION, LightPos);
    float LightDif[4] = {.5f, .5f, 1.f, 1.f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
    glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .01f);
    Point top(0, 0, 0);
    Vector ax = Vector::UP;
    Cone c(0.5, 2, 12, top, ax);
    glColor3f(1.0f, 1.0f, 1.0f);
    c.draw(true);

    glDisable(GL_LIGHTING);
    //glColor3f(1.0f,1.0f,1.0f);
    glutSwapBuffers();
}
