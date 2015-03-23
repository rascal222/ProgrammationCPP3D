#include "../primitives/Cylinder.hpp"
#include <GL/glut.h>
#include "../core/PolarPoint.hpp"
#include "../glWrappers/GlCoreRendering.hpp"
#include "../octree/AdaptativeOctree.hpp"
#include "../glWrappers/EulerCamera.hpp"
#include "../primitives/Sphere.hpp"
#include "../octree/UnionAdaptiveOctree.hpp"


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
float angle = 0.0, angle2 = 0.0;

float xOrigin = -1;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

void mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_DOWN) {// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

void mouseMove(int x, int y) {

    // this will only be true when the left button is down
    if (xOrigin >= 0) {
        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.01f;

    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT :
            deltaAngle = 0.0f;
            break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN :
            deltaMove = 0;
            break;
    }
}

bool debug = false;
EulerCamera eulerCamera(0, 0, 0, 5);
Point pK(0, 0, 0);
Voxel v(pK, 20);
Cylinder *s = nullptr;
Sphere *s2 = nullptr;
UnionAdaptiveOctree *ao = nullptr;

int main(int argc, char **argv) {
    // init GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(window_display);
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
    gluPerspective(45, ratio, 1, 100);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void window_special_key(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT :
            deltaAngle = -0.3f;
            break;
        case GLUT_KEY_RIGHT :
            deltaAngle = 0.3f;
            break;
        case GLUT_KEY_UP :
            deltaMove = 0.3f;
            break;
        case GLUT_KEY_DOWN :
            deltaMove = -0.3f;
            break;
    }
    //glutPostRedisplay(); // just update here....
}

GLvoid initGL() {
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

void init_scene() {
    s = new Cylinder(7, 15, 20, pK);
    Point p = pK.translate(Vector::FORWARD);
    for (int i = 0; i < 3; ++i)
        p = p.translate(Vector::FORWARD);
    s2 = new Sphere(6, 12, 12, p);
    ao = new UnionAdaptiveOctree(v, s2, s, 5);
    ao->compute();
}


GLvoid window_display() {
    renderScene();
    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

}


GLvoid window_key(unsigned char key, int x, int y) {
    switch (key) {
        case 9:
            debug = !debug;
            break;
        default:
            printf("The key '%c' (%d) is off", key, key);
    }
    glutPostRedisplay();
}


void reper() {
    glDisable(GL_LIGHTING);
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

void lighting() {
    int LightPos[3] = {1, 1, 0};
    int LightAmbient[4] = {0, 0, 0, 1};
    int LightDiffuse[4] = {1, 1, 1, 1};

    float GlobalLightAmbient[4] = {1.f, 1.f, 0.2f, 1.f};

    int MatSpec[4] = {1, 1, 1, 1};
    int MatEmission[4] = {0, 0, 0, 1};
    glLightiv(GL_LIGHT0, GL_POSITION, LightPos);
    glLightiv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightiv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightModelfv(
            GL_LIGHT_MODEL_AMBIENT, GlobalLightAmbient);
    glLightiv(GL_LIGHT0, GL_POSITION, LightPos);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    glColorMaterial(GL_COLOR_MATERIAL, GL_AMBIENT_AND_DIFFUSE);
    glMaterialiv(GL_COLOR_MATERIAL, GL_SPECULAR, MatSpec);
    glMaterialiv(GL_COLOR_MATERIAL, GL_EMISSION, MatEmission);


}

void renderScene() {
    eulerCamera.computeEvent(deltaMove, 0.0f, deltaAngle, 0.0f);
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Set the camera
    //lighting();
    eulerCamera.place();

    if (!debug)
        lighting();

    ao->draw(false, !debug);
    if (debug) {
        s->draw(true);
        s2->draw(true);
    }
    //reper();

    glDisable(GL_LIGHTING);
    glutSwapBuffers();
}
