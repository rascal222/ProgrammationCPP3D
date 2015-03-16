#include <GL/gl.h>
#include <GL/glut.h>
#include "../primitives/Sphere.hpp"
#include <cmath>
#include "../core/EulerCamera.hpp"
#include <GL/glut.h>
#include <GL/gl.h>
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

int LightPos[4] = {0, 0, 0, 1};
int MatSpec [4] = {1,1,1,1};
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

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f; break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0.0f; break;
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


    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

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
    }
    //glutPostRedisplay(); // just update here....
}

GLvoid initGL()
{
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

void init_scene()
{
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

Sphere c;
bool debug=true;
GLvoid window_key(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 9:
            debug!=debug;
            if(debug)
                printf("debug on");
            else
                printf("debug off");
            break;
        case 43://+
            c.setMeridians(c.getMeridians()+1);
            break;
        case 45://-
            if(c.getMeridians()>2)
                c.setMeridians(c.getMeridians()-1);
            break;
        case 42://*
            c.setParalleles(c.getParalleles()+1);
            break;
        case 47:// /
            if(c.getParalleles()>2)
                c.setParalleles(c.getParalleles()-1);
            break;
        default:
            printf("Key %c %d is offline.",key,key);
    }
    glutPostRedisplay();
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


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!debug) {
        glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
        glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        LightPos[0] = 0;
        LightPos[1] = 2;
        LightPos[2] = 2;
        glLightiv(GL_LIGHT0, GL_POSITION, LightPos);
        float LightDif[4] = {0.f, 1.f, 1.f, 1.f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .05f);
        GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    }
    // Reset transformations
    glLoadIdentity();
    // Set the camera

    gluLookAt(	x, y, z,
            x+lx,y+ly,z+lz,
            0.0f, 1.0f,  0.0f);

    glMatrixMode(GL_MODELVIEW);


    glColor3f(1.0f,1.0f,1.0f);
    c.draw(debug);
    if(!debug)
    {
        glDisable(GL_LIGHTING);
    }

    glColor3f(1.0,1.0f,1.0f);
    glBegin(GL_QUADS);
    {
        glVertex3f(-5.f,-5.f,-5.f);
        glVertex3f(-5.f,-1.f,5.f);
        glVertex3f(5.f,-1.f,5.f);
        glVertex3f(5.f,-1.f,-5.f);

    }
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
    glutSwapBuffers();
}
