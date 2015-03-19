#include "Cylinder.hpp"
#include "../core/Point.hpp"
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <iostream>
namespace prog_3D {

	Cylinder::Cylinder() {
		center = Point::Origin;
		rayon = 3.0f;
		height = 25.0f;
		meridians = 10;
	}

	Cylinder::Cylinder(float rayon, float height,int meridians, Point& center)
	{
		this->center = center;
		this->rayon=rayon;
		this->height=height;
		this->meridians=meridians;
	}

	Cylinder::~Cylinder() {
	}

	void Cylinder::draw() {
		draw(false);
	}

	void Cylinder::draw(bool debug) {
		std::vector<Point> top;
		std::vector<Point> down;

		for (int i = 0; i < meridians; ++i) {
			double angle = 2* M_PI*i / meridians;
			double x = rayon * cos(angle) + center.getX();
			double y = rayon * sin(angle) + center.getY();
			Point t(x, y, center.getZ() + (height / 2));
			Point d(x, y, center.getZ() - (height / 2));
			top.push_back(t);
			down.push_back(d);

			if(debug)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_LINES);
				{
					glVertex3f(t.getX(), t.getY(), t.getZ());
					glVertex3f(d.getX(), d.getY(), d.getZ());

				}
				glEnd();
			}
		}
        //Face down
        glBegin(GL_LINE_STRIP);
        {
            for(int i=0;i<meridians;++i)
                glVertex3f(down.at(i).getX(), down.at(i).getY(), down.at(i).getZ());

            glVertex3f(down.at(0).getX(), down.at(0).getY(), down.at(0).getZ());
        }
        glEnd();


		glBegin(GL_QUAD_STRIP);
		{
			for(int i=0;i< meridians;++i) {

				glVertex3f(top.at(i).getX(), top.at(i).getY(), top.at(i).getZ());
				glVertex3f(down.at(i).getX(), down.at(i).getY(), down.at(i).getZ());
			}
            glVertex3f(top.at(0).getX(), top.at(0).getY(), top.at(0).getZ());
            glVertex3f(down.at(0).getX(), down.at(0).getY(), down.at(0).getZ());


		}
		glEnd();
	}

	float Cylinder::equation(const Point& point)
	{
		float powCenter = pow(p.getX(), 2) + pow(p.getY(), 2) + pow(p.getZ(), 2);
		float powCylinderAxe = pow(Vector::FORWARD.getX(), 2) + pow(Vector::FORWARD.getY(), 2) + pow(Vector::FORWARD.getZ(), 2);
		Vector v(Vector::FORWARD);
		v.setX(v.getX()* p.getX());
		v.setY(v.getY()* p.getY());
		v.setZ(v.getZ()* p.getZ());
		float centerMulti = pow(v.getX()+, 2);
		float division = centerMulti / powCylinderAxe;
		float minus = powCenter - division;
		float powR = pow(rayon, 2);
		return minus - powR;
	}
}
