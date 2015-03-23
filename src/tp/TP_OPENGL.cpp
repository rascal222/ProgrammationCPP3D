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
#include "../curves/BezierCurve.hpp"
#include "../curves/HermiteCubicCurve.hpp"
#include "../curves/DeCasteljauBezierCurve.hpp"
#include "../curves/BernsteinBezierCurve.hpp"

#include "../glWrappers/GlCoreRendering.hpp"
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
	//glEnable(GL_LIGHT0);
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

	//glutKeyboardUpFunc(&window_key);

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
			//SCENE;
		case 9://TAB
			op=!op;
			break;
		case 38://&
			std::cout << "HermiteCubicCurve"<<std::endl;
			scene=1;
			c.reset();
			break;
		case 233://é
			std::cout << "BezierCurve (Bernstein)"<<std::endl;
			scene=2;
			c.reset();
			break;
		case 34://"
			std::cout << "BezierCurve (DeCasteljau)"<<std::endl;
			scene=3;
			c.reset();
			break;
		case 119: //w
			std::cout << "Decrease number of computed points"<<std::endl;
			if(c->getPointsNumber()>3)
				c->setPointsNumber(c->getPointsNumber()-1);
			break;
		case 120: //x
			std::cout << "Increase number of computed points"<<std::endl;
			c->setPointsNumber(c->getPointsNumber()+1);
			break;
		case 97: // a
			std::cout << "Decrease modifier value"<<std::endl;
			if(numModifier>0)
				numModifier--;
			std::cout << "Current -> "<<numModifier;
			break;
		case 122: // z
			//loop entre les modifier de contrôle
			std::cout << "Increase modifier value"<<std::endl;
			if(numModifier<modifierMax)
				++numModifier;
			if(numModifier==modifierMax)
				numModifier=0;
			std::cout << "Current -> "<<numModifier;
			break;
		case 101: // e
			//ADD A CONTROL POINT
			std::cout <<" Only on Bezier Curve" <<std::endl;
			if(scene==2 || scene==3)
			{
				std::cout << "Add a control point on the last one" << std::endl;
				BezierCurve* c2 = dynamic_cast<BezierCurve*>(c.get());
				int size = c2->getControlPoint().size();
				Point p2 = c2->getControlPoint().at(size-1);
				Point d(p2.getX(),p2.getY(),p2.getZ());
				c2->getControlPoint().push_back(d);
				numModifier=size;
				modifierMax=c2->getControlPoint().size()+1;
			}
			break;
			//printf ("La touche %c est active.\n", key);
		case 114: // r
			std::cout <<" Only on Bezier Curve" <<std::endl;

			if(scene==2 || scene==3)
			{
				std::cout << "Remove the current control point" << std::endl;
				BezierCurve* c2 = dynamic_cast<BezierCurve*>(c.get());
				if(c2->getControlPoint().size()>2) {
					c2->getControlPoint().erase(c2->getControlPoint().begin() + numModifier);
					modifierMax = c2->getControlPoint().size() - 1;
				}
			}

			break;
		case 111: // o (haut)
			if(scene==1)
			{
				std::cout << ""<<numModifier << std::endl;
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
				else if(numModifier==3)
				{
					//Move V1 y++
					c2->getVector2().setY(c2->getVector2().getY()+.4);
				}
			}
			else if(scene==2 || scene==3) {
				BezierCurve *c2 = dynamic_cast<BezierCurve *>(c.get());
				c2->getControlPoint().at(numModifier).setY(c2->getControlPoint().at(numModifier).getY() + 0.4);
			}

			break;
		case 108: // l (bas)
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
				else if(numModifier==3)
				{
					//Move V1 y++
					c2->getVector2().setY(c2->getVector2().getY()-.4);
				}
			}
			else if(scene==2 || scene==3)
			{
				BezierCurve* c2 = dynamic_cast<BezierCurve*>( c.get());
				c2->getControlPoint().at(numModifier).setY(c2->getControlPoint().at(numModifier).getY()-0.4);
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
				else if(numModifier==3)
				{
					//Move V1 y++
					c2->getVector2().setX(c2->getVector2().getX()-.4);
				}
			}
			else if(scene==2||scene==3)
			{
				BezierCurve* c2 = dynamic_cast<BezierCurve*>( c.get());
				c2->getControlPoint().at(numModifier).setX(c2->getControlPoint().at(numModifier).getX()-0.4);
			}
			break;
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
				else if(numModifier==3)
				{
					//Move V1 y++
					c2->getVector2().setX(c2->getVector2().getX()+.4);
				}
			}
			else if(scene==2 || scene==3)
			{
				BezierCurve* c2 = dynamic_cast<BezierCurve*>( c.get());
				c2->getControlPoint().at(numModifier).setX(c2->getControlPoint().at(numModifier).getX()+0.4);
			}
			break;
		default:
			printf ("La touche %d n´est pas active.\n", key);
			break;
	}

	render_scene();
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




void drawIntermediate(double u,std::vector<Point> ps,int step)
{
	if(ps.size()==1) {
		drawPoint(ps.at(0));
		return;
	}
	std::vector<Point> poin2;
	for (int k = 0; k < ps.size() - 1; ++k) {
		double x = ps[k].getX() * (1.0 - u) + u * ps[k + 1].getX();
		double y = ps[k].getY() * (1.0 - u) + u * ps[k + 1].getY();
		double z =ps[k].getZ() * (1.0 - u) + u * ps[k + 1].getZ();

		Point p(x, y, z);
		poin2.push_back(p);
	}
	if(step==0)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(step==1)
		glColor3f(0.0f, 1.0f, 1.0f);
	else if(step==3)
		glColor3f(0.0f, 0.0f, 1.0f);
	else if(step==4)
		glColor3f(1.0f, 1.0f, 0.0f);


	if(poin2.size()>1) {
		drawCurve(poin2, true);
	}
	drawIntermediate(u
			,poin2,++step);
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
			numModifier=0;
			Point p(4,0,0);
			Point o = Point::Origin;
			Vector v0 = Vector::UP;
			Vector v1 = Vector::DOWN;
			modifierMax=4;
			c.reset(new HermiteCubicCurve(o,p,v0,v1,numberOfPoint));
		}
		else if(scene==2)
		{
			numModifier=0;
			std::vector<Point> vect;
			vect.push_back(Point::Origin);
			Point p(1,4,0);vect.push_back(p);
			Point p2(4,0,0);vect.push_back(p2);
			modifierMax=3;
			c.reset(new BernsteinBezierCurve(vect,numberOfPoint));
		}
		else
		{
			numModifier=0;
			std::vector<Point> vect;
			vect.push_back(Point::Origin);
			Point p(1,4,0);vect.push_back(p);
			Point p2(4,0,0);vect.push_back(p2);
			modifierMax=3;

			c.reset(new DeCasteljauBezierCurve(vect,numberOfPoint));

		}
	}

	if(c)
	{
		drawCurve(c->compute(),op);
		if(scene==1 && op)
		{
			HermiteCubicCurve* c2 = dynamic_cast<HermiteCubicCurve*>(c.get());
			glColor3f(1.0f,0.0f,0.0f);
			drawLine(c2->getPoint1(), c2->getVector1());
			drawLine(c2->getPoint2(), c2->getVector2());
			glColor3f(1.0f,1.0f,1.0f);
		}
		else if(op && (scene==2 || scene==3))
		{
			BezierCurve* c2 = dynamic_cast<BezierCurve*>(c.get());
			//Draw Control Points Curve


			if(scene==3) {
				//Need to draw every round of



				for (long i = 0; i < c2->getPointsNumber(); ++i) {
					double u = ((double) i) * 1.0 / (double) (c2->getPointsNumber() - 1);
					drawIntermediate(u,c2->getControlPoint(),0);


				}
			}
			glColor3f(1.0f,0.0f,0.0f);
			drawCurve(c2->getControlPoint(), op);

		}


	}

	glFlush();
}
