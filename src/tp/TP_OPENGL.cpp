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

/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>.
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h"
*/

#include <GL/glut.h>
#include <term.h>


#include "../core/Point.hpp"
#include "../core/Vector.hpp"

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

    // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
    // à une fonction (render_scene() ici) qui contient les informations
    // que l'on veut dessiner
    render_scene();

    // trace la scène grapnique qui vient juste d'être définie
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
    // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
    // de trop grosse taille par rapport à la fenêtre.
    glOrtho(0,5,-5.0, 5.0, -2.0, 2.0);

    // toutes les transformations suivantes s´appliquent au modèle de vue
    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
    switch (key) {
        case KEY_ESC:
            exit(1);
            break;

        default:
            printf ("La touche %d n´est pas active.\n", key);
            break;
    }
}



/// \brief génère un point opengl
void glPoint(const Point& p)
{

    glVertex3d(p.getX(),p.getY(),p.getZ());
}


/// \brief dessine une instance de classe Point
void drawPoint(const Point& p)
{
    glPointSize(5);
    glBegin(GL_POINTS);

    glPoint(p);
    glEnd();
}

/// \brief
void drawLine(const Point& p,const Vector& v)
{
    glBegin(GL_LINES);
    glPoint(p);
    Point p2 = p.translate(v);
    glPoint(p2);
    glEnd();
}

void drawLine(Point& p, Point& p2)
{
    glBegin(GL_LINES);
    glPoint(p);
    glPoint(p2);
    glEnd();
}


void drawCurve(Point tabPointsOfCurve[], long nbPoints)
{
    for(int i=0;i<nbPoints-1;i++) {
        drawLine(tabPointsOfCurve[i], tabPointsOfCurve[i + 1]);
        drawPoint(tabPointsOfCurve[i]);
        drawPoint(tabPointsOfCurve[i+1]);
    }
}


Point* hermiteCubicCurve(const Point& p0, const Point& p1, const Vector& v0, const Vector& v1,long nbU)
{
    Point* tab1 = new Point[nbU+2];
    tab1[0]=p0;
    tab1[nbU+1]=p1;
    for(long i=1;i<=nbU;i++)
    {
        double u = ((double) i) *1.0 /(double)(nbU+1);

        double f1 = 2 * pow(u,3) - 3 * pow(u,2) + 1;
        double f2 = -2 * pow(u,3) + 3 * pow(u,2);
        double f3 = pow(u,3) - 2 * pow(u,2) + u;
        double f4 = pow(u,3) - pow(u,2);

        double x = f1*p0.getX() + f2*p1.getX() + f3*v0.getX() + f4*v1.getX();
        double y = f1*p0.getY() + f2*p1.getY() + f3*v0.getY() + f4*v1.getY();
        double z = f1*p0.getZ() + f2*p1.getZ() + f3*v0.getZ() + f4*v1.getZ();
        tab1[i].setX(x);
        tab1[i].setY(y);
        tab1[i].setZ(z);
    }

    return tab1;
}
double fact(double n)
{
    return (n == 1.0 || n == 0.0) ? 1.0 : fact(n - 1.0) * n;
}
/*
double bernstein(long n, long i, double u)
{
   // double top = factorial(n) / factorial(i) * factorial(n-i);
    double mid = pow(u,i);
    double bot = pow ((1-u), n-1);
    return top*mid*bot;
}*/

Point* bezierCurveByBernstein(Point* tabControlPoint, long nbControlPoint, long nbU)
{
    Point* tab1 = new Point[nbU];
   // tab1[0]=tabControlPoint[0];
   // tab1[nbU+1]=tabControlPoint[nbControlPoint-1];
    for(long i=0;i<nbU;++i)
    {
        double u = ((double) i) * 1.0 /(double)(nbU);
        double x=0;
        double y =0;
        double z=0;
        // LA SOMME DES POINTS DE CONTROLES EN FONCTION DE U
        for(long j=0;j<nbControlPoint;++j)
        {
            double b = (fact(nbControlPoint-1) / (fact(j) * fact(nbControlPoint-1-j))) * pow(u, j) * pow((1.0-u), nbControlPoint-1-j);
            x+= b*(double) tabControlPoint[j].getX();
            y+= b*(double) tabControlPoint[j].getY();
            z+= b*(double) tabControlPoint[j].getZ();
        }

        tab1[i].setX(x);
        tab1[i].setY(y);
        tab1[i].setZ(z);
    }

    return tab1;

}

//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
    glColor3f(1.0, 1.0, 1.0);


    //  Nous créons ici un polygone. Nous pourrions aussi créer un triangle ou des lignes. Voir ci-dessous les parties
    // en commentaires (il faut commenter le bloc qui ne vous intéresse pas et décommenter celui que vous voulez tester.
/*

    Point origin(0,0,0);



    Point a1(0,-1,0);
    Point a2(1,0,0);
    Point a3(-0.5,1,0);

    Vector l(a1,a2);
    drawPoint(origin);

    drawLine(a1, l);
    Vector r(1,0,0);
    drawLine(a3,r);

    glColor4f(1.0,0.0,0,1);
    Point p = origin.projectOnLine(l,a1);
    drawPoint(p);
    p = origin.projectOnLine(r,a3);
    drawPoint(p);
    std::cout << p << std::endl;
    */

    Point P0(0,0,0);
    Point P1(4,0,0);
    Point P1b(1,2,0);

    Vector V1(1,1,0);
    Vector V2(1,-1,0);

    glColor3f(1.0,0.0,0.0);
    drawLine(P0,V1);
    drawLine(P1,V2);
    glColor3f(1.0,1.0,1.0);
    int n = 10;
    //Point* tab2 = hermiteCubicCurve(P0, P1, V1, V2,n);//Return n+2 points
    Point p[3];
    p[0]=P0;
    p[1]=P1b;
    p[2]=P1;
   Point* tab2= bezierCurveByBernstein(p,3, n);
    drawCurve(tab2, n);
    glColor3f(0.0,1.0,0.0);
    drawCurve(p,3);

    int nbr = 4;
    Point* pts3 = new Point[nbr];
    pts3[0]=Point(0,0,0);
    pts3[1] =Point(1,2,0);
    pts3[2] =Point(2,-3,0);
    pts3[3] =Point(3,2,0);
    Point* pts2 = bezierCurveByBernstein(pts3, nbr, 10);
    drawCurve(pts2, 10);
    glColor3f(1.0, 0, 0);
    drawCurve(pts3, nbr);
}
