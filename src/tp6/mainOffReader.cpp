
#include <GL/glut.h>
#include "../glWrappers/GlCoreRendering.hpp"

#include "../glWrappers/EulerCamera.hpp"

#include "../meshing/Mesh.hpp"
#include "../meshing/OffManipulator.hpp"


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
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}

EulerCamera eulerCamera(0, 0, 0, 5);
Point pK(0, 0, 0);
Mesh m;

int main(int argc, char **argv)
{
    // init GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(window_display);
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
        case GLUT_KEY_LEFT :
            deltaAngle = -0.15f;
            break;
        case GLUT_KEY_RIGHT :
            deltaAngle = 0.15f;
            break;
        case GLUT_KEY_UP :
            deltaMove = 0.15f;
            break;
        case GLUT_KEY_DOWN :
            deltaMove = -0.15f;
            break;
        default:
            break;
    }
    //glutPostRedisplay(); // just update here....
}

GLvoid initGL()
{
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

void init_scene()
{
    OffManipulator off;
    m = off.read("bunny.off");
}


GLvoid window_display()
{
    renderScene();
    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-WIDTH/2, WIDTH/2,-HEIGHT/2, HEIGHT/2, -2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

}


GLvoid window_key(unsigned char key, int x, int y)
{
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
    int LightPos[4] = {0, 4, 3, 1};
    int MatSpec[4] = {1, 1, 1, 1};
    // Clear Color and Depth Buffers
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightiv(GL_LIGHT0, GL_POSITION, LightPos);
    float LightDif[4] = {.5f, .5f, 1.f, 1.f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
    glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .01f);
}

void renderScene()
{
    eulerCamera.computeEvent(deltaMove, 0.0f, deltaAngle, 0.0f);
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Set the camera
   // lighting();
    eulerCamera.place();

    for(unsigned long i=0;i<m.idTriangles.size();++i)
    {
        std::cout << m.idTriangles.size()<<std::endl;
        std::cout << m.points.size() <<std::endl;
        prog_3D::wireframeTriangle
                (
                m.points.at((unsigned long)m.idTriangles.at(i).getPointId(0)),
                m.points.at((unsigned long)m.idTriangles.at(i).getPointId(1)),
                m.points.at((unsigned long)m.idTriangles.at(i).getPointId(2))
        );
    }

    glutSwapBuffers();
}
