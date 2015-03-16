#include <GL/gl.h>
#include <GL/glut.h>
#include "../primitives/Cone.hpp"
#include "../primitives/Cylinder.hpp"
#include <cmath>

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
// angle of rotation for the camera direction
float angle = 0.0;
float angle2 = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;
// XZ position of the camera
float x = 0.0f, y = 1.0f, z = 5.0f;
float r = 5.0f;
int xOrigin = -1;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle1 = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;

void mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle1;
            xOrigin = -1;
        }
        else {// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

void mouseMove(int x, int y) {


}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT :
            deltaAngle1 = 0.0f;
            break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN :
            deltaAngle2 = 0.0f;
            break;
    }
}

int main(int argc, char **argv) {
    // init GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
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

    float ratio = w * 1.0 / h;

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
            deltaAngle1 = -0.50f;
            break;
        case GLUT_KEY_RIGHT :
            deltaAngle1 = 0.50f;
            break;
        case GLUT_KEY_UP :
            deltaAngle2 = 0.5f;
            break;
        case GLUT_KEY_DOWN :
            deltaAngle2 = -0.5f;
            break;
    }
    //glutPostRedisplay(); // just update here....
}

GLvoid initGL() {
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

void init_scene() {
}


GLvoid window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
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

void computePos(float deltaMove) {

    r += deltaMove;
    x = r * cos(angle);
    y = r * tan(angle2);
    z = r * sin(angle);

}

void computeDir(float deltaAngle1, float deltaAngle2) {


    angle += deltaAngle1 * 10;
    angle2 += deltaAngle2 * 1;
}

void renderScene() {
    if (deltaAngle1 || deltaAngle2)
        computeDir(deltaAngle1, deltaAngle2);
    computePos(deltaMove);

    // Clear Color and Depth Buffers
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera



// Calculate the camera position using the distance and angles
    float camX = r * -sinf(angle * (M_PI / 180)) * cosf((angle2) * (M_PI / 180));
    float camY = r * -sinf((angle2) * (M_PI / 180));
    float camZ = -r * cosf((angle) * (M_PI / 180)) * cosf((angle2) * (M_PI / 180));

// Set the camera position and lookat point
    gluLookAt(camX, camY, camZ,   // Camera position
            0.0, 0.0, 0.0,    // Look at point
            0.0, 1.0, 0.0);   // Up vector

    LightPos[0] = 0;
    LightPos[1] = 0;
    LightPos[2] = 0;
    glLightiv(GL_LIGHT0, GL_POSITION, LightPos);
    float LightDif[4] = {.5f, .5f, 1.f, 1.f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
    glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .01f);

    glMatrixMode(GL_MODELVIEW);

    Point top(0, 0, 0);
    Vector ax = Vector::UP;
    Cone c(0.5, 2, 6, top, ax);
    glColor3f(1.0f, 1.0f, 1.0f);
    c.draw(true);
    Cylinder c2;
    //c2.draw(true);
    glDisable(GL_LIGHTING);
    //glColor3f(1.0f,1.0f,1.0f);
    glutSwapBuffers();
}
