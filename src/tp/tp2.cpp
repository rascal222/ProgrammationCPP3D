///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include <memory>

/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>.
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h"
*/

#include <GL/glut.h>


#include "../core/Point.hpp"
#include "../core/Vector.hpp"
#include "../core/Curve.hpp"
#include "../core/HermiteCubicCurve.hpp"
#include "../core/BernsteinBezierCurve.hpp"
#include "../core/DeCasteljauBezierCurve.hpp"
// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27

using namespace prog_3D;
using namespace std;

// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


int main(int argc, char **argv)
{
    // initialisation  des paramètres de GLUT en fonction
    // des arguments sur la ligne de commande
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    // définition et création de la fenêtre graphique, ainsi que son titre
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Premier exemple : carre");
    glEnable(GL_LIGHT0);
    // initialisation de OpenGL et de la scène
    initGL();
    init_scene();

    // choix des procédures de callback pour
    // le tracé graphique
    glutDisplayFunc(&window_display);
    // le redimensionnement de la fenêtre
    glutReshapeFunc(&window_reshape);
    // la gestion des événements clavier
    glutKeyboardFunc(&window_key);

    glutKeyboardUpFunc(&window_key);

    // la boucle prinicipale de gestion des événements utilisateur
    glutMainLoop();

    return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL()
{
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    render_scene();
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,5,-5.0, 5.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier


bool op=false;
short scene=1;
std::shared_ptr<Curve> c(nullptr);
int numberOfPoint=10;
int numModifier=0;
int modifierMax=2;

GLvoid window_key(unsigned char key, int x, int y)
{
    render_scene();
}


void render_scene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glFlush();
}
