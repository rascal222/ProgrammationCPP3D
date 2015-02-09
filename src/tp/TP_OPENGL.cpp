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
#include <term.h>


#include "../core/Point.hpp"
#include "../core/Vector.hpp"
#include "../core/Curve.hpp"
#include "../core/HermiteCubicCurve.hpp"
#include "../core/BernsteinBezierCurve.hpp"

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
	// ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
	// possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
	// de trop grosse taille par rapport à la fenêtre.
	glOrtho(0,5,-5.0, 5.0, -2.0, 2.0);
	// toutes les transformations suivantes s´appliquent au modèle de vue
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
	//CAN'T BE SEE, BUT BE DONE
	switch (key) {
		case KEY_ESC:
			exit(1);
			break;
			//SCENE;
		case 38://&
			scene=1;
			c.reset();
			break;
		case 233://é
			scene=2;
			c.reset();
			break;
		case 34://"
			scene=3;
			c.reset();
			break;

		case 97: // a
			std::cout << ""<<numModifier << std::endl;

				numModifier--;
			break;
		case 122: // z
			//loop entre les modifier de contrôle
		   ++numModifier;
		std::cout << ""<<numModifier << std::endl;
			break;
		case 101: // e
			//ADD A CONTROL POINT
			if(scene==2)
			{
				BernsteinBezierCurve* c2 = dynamic_cast<BernsteinBezierCurve*>(c.get());
				int size = c2->getControlPoint().size();
				Point p2 = c2->getControlPoint().at(size-1);
				Point d(p2.getX(),p2.getY(),p2.getZ());
				c2->getControlPoint().push_back(d);
				numModifier=size;
			}
			else if(scene==3)
			{
				/* DeCasteljauBezierCurve* c2 = dynamic_cast<DeCasteljauBezierCurve*>(c.get());
				int size = c2->getControlPoint().size();
				Point p2 = c2->getControlPoint().at(size-1);
				Point d(p2.getX(),p2.getY(),p2.getZ());
				c2->getControlPoint().push_back(d);
				numModifier=size;*/
			}
			break;
			//printf ("La touche %c est active.\n", key);
		case 114: // r
			if(scene==2)
			{
				BernsteinBezierCurve* c2 = dynamic_cast<BernsteinBezierCurve*>(c.get());
				c2->getControlPoint().erase(c2->getControlPoint().begin() + numModifier);
			}
			else if(scene==3)
			{
				// DeCasteljauBezierCurve* c2 = dynamic_cast<DeCasteljauBezierCurve*>(c.get());
				// c2->getControlPoint().erase(c2->getControlPoint().begin() + numModifier);
			} break;
		case 111: // o (haut)
			if(scene==1)
			{
				HermiteCubicCurve* c2 = dynamic_cast<HermiteCubicCurve*>(c.get());
				if(numModifier==0)
				{
					//Move P0 y++
					c2->getPoint1().setY(c2->getPoint1().getY()+.4);
				}
				else if(numModifier==1)
				{
					//Move P1 y++
					c2->getPoint2().setY(c2->getPoint2().getY()+.4);
				}
				else if(numModifier==2)
				{
					//Move V0 y++
					c2->getVector1().setY(c2->getVector1().getY()+.4);
				}
				else if(numModifier==2)
				{
					//Move V1 y++
					c2->getVector2().setY(c2->getVector2().getY()+.4);
				}
			}
			else if(scene==2)
			{
				BernsteinBezierCurve* c2 = dynamic_cast<BernsteinBezierCurve*>(c.get());
				c2->getControlPoint().at(numModifier).setY(c2->getControlPoint().at(numModifier).getY()+0.4);

				// remove numModifier

			}
			else if(scene==3)
			{
			   // DeCasteljauBezierCurve* c2 = (DeCasteljauBezierCurve*) c.get();
			   // c2->getControlPoint().at(numModifier).setY(c2->getControlPoint().at(numModifier).getY()+0.4);
			}
			printf ("La touche %c est active.\n", key);break;
		case 108: // l (bas)
			printf ("La touche %c est active.\n", key);
			if(scene==1)
			{
				HermiteCubicCurve* c2 = dynamic_cast<HermiteCubicCurve*>( c.get());
				if(numModifier==0)
				{
					//Move P0 y++
					c2->getPoint1().setY(c2->getPoint1().getY()-.4);
				}
				else if(numModifier==1)
				{
					//Move P1 y++
					c2->getPoint2().setY(c2->getPoint2().getY()-.4);
				}
				else if(numModifier==2)
				{
					//Move V0 y++
					c2->getVector1().setY(c2->getVector1().getY()-.4);
				}
				else if(numModifier==2)
				{
					//Move V1 y++
					c2->getVector2().setY(c2->getVector2().getY()-.4);
				}
			}
			else if(scene==2)
			{
				BernsteinBezierCurve* c2 = dynamic_cast<BernsteinBezierCurve*>( c.get());
				c2->getControlPoint().at(numModifier).setY(c2->getControlPoint().at(numModifier).getY()-0.4);
			}
			else if(scene==3)
			{

			}
			break;
		case 107: // k (gauche)
			if(scene==1)
			{
				HermiteCubicCurve* c2 = dynamic_cast<HermiteCubicCurve*>( c.get());
				if(numModifier==0)
				{
					//Move P0 y++
					c2->getPoint1().setX(c2->getPoint1().getX()-.4);
				}
				else if(numModifier==1)
				{
					//Move P1 y++
					c2->getPoint2().setX(c2->getPoint2().getX()-.4);
				}
				else if(numModifier==2)
				{
					//Move V0 y++
					c2->getVector1().setX(c2->getVector1().getX()-.4);
				}
				else if(numModifier==2)
				{
					//Move V1 y++
					c2->getVector2().setX(c2->getVector2().getX()-.4);
				}
			}
			else if(scene==2)
			{
				BernsteinBezierCurve* c2 = dynamic_cast<BernsteinBezierCurve*>( c.get());
				c2->getControlPoint().at(numModifier).setX(c2->getControlPoint().at(numModifier).getX()-0.4);
			}
			else if(scene==3)
			{

			};break;
		case 109: // k (droite)
			if(scene==1)
			{
				HermiteCubicCurve* c2 = dynamic_cast<HermiteCubicCurve*>( c.get());
				if(numModifier==0)
				{
					//Move P0 y++
					c2->getPoint1().setX(c2->getPoint1().getX()+.4);
				}
				else if(numModifier==1)
				{
					//Move P1 y++
					c2->getPoint2().setX(c2->getPoint2().getX()+.4);
				}
				else if(numModifier==2)
				{
					//Move V0 y++
					c2->getVector1().setX(c2->getVector1().getX()+.4);
				}
				else if(numModifier==2)
				{
					//Move V1 y++
					c2->getVector2().setX(c2->getVector2().getX()+.4);
				}
			}
			else if(scene==2)
			{
				BernsteinBezierCurve* c2 = dynamic_cast<BernsteinBezierCurve*>( c.get());
				c2->getControlPoint().at(numModifier).setX(c2->getControlPoint().at(numModifier).getX()+0.4);
			}
			else if(scene==3)
			{

			}
			;break;
		default:
			printf ("La touche %d n´est pas active.\n", key);
			break;
	}

	render_scene();
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

void drawPoint(Point& p,float r,float g,float b)
{
	glColor3f(r,g,b);
	glBegin(GL_POINTS);
	glPoint(p);
	glEnd();
}


void drawPoint(Point& p,float r,float g,float b, float alpha)
{
	glColor4f(r,g,b,alpha);
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

void drawCurve(Point tabPointsOfCurve[], long nbPoints,bool showPoint)
{
	for(int i=0;i<nbPoints-1;++i) {
		drawLine(tabPointsOfCurve[i], tabPointsOfCurve[i + 1]);
		if(showPoint)
		{
			drawPoint(tabPointsOfCurve[i]);
			drawPoint(tabPointsOfCurve[i + 1]);
		}
	}
}

void drawCurve(Point tabPointsOfCurve[], long nbPoints)
{
	drawCurve(tabPointsOfCurve, nbPoints,false);
}

void drawCurve(std::vector<Point> tabPointsOfCurve,bool showPoint)
{
	for(int i=0;i<tabPointsOfCurve.size()-1;++i) {
		drawLine(tabPointsOfCurve.at(i), tabPointsOfCurve.at(i+1));
		if(showPoint)
		{
			drawPoint(tabPointsOfCurve[i]);
			drawPoint(tabPointsOfCurve[i + 1]);
		}
	}
}

void drawCurve(std::vector<Point> tabPointsOfCurve)
{
	drawCurve(tabPointsOfCurve, false);
}

void drawCurve(Curve& curve)
{
	drawCurve(curve.compute(), false);
}

void drawCurve(Curve& curve,bool debug)
{
	drawCurve(curve.compute(), debug);
}


void render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	if(!c)
	{
		numberOfPoint=10;
		if(scene==1)
		{
			Point p(4,0,0);
			Point o = Point::Origin;
			Vector v0 = Vector::UP;
			Vector v1 = Vector::DOWN;
			modifierMax=4;
			c.reset(new HermiteCubicCurve(o,p,v0,v1,numberOfPoint));
		}
		else if(scene==2)
		{
			std::vector<Point> vect;
			vect.push_back(Point::Origin);
			Point p(1,4,0);vect.push_back(p);
			Point p2(4,0,0);vect.push_back(p2);
			modifierMax=2;
			c.reset(new BernsteinBezierCurve(vect,numberOfPoint));
		}
		else
		{
			std::vector<Point> vect;
			vect.push_back(Point::Origin);
			Point p(1,4,0);vect.push_back(p);
			Point p2(4,0,0);vect.push_back(p2);
			modifierMax=2;
			//c.reset(new CasteljauBezierCurve(vect,numberOfPoint));

		}
	}

	drawCurve(c->compute(),op);
	glFlush();
}
