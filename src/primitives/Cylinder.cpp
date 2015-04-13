#include "Cylinder.hpp"
#include "../core/Vector.hpp"
#include <cmath>
#include <GL/glut.h>
#include <iostream>
namespace prog_3D {

	Cylinder::Cylinder() {
		center = Point::Origin;
		rayon = 3.0f;
		height = 5.0f;
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

	std::vector<std::vector<Point>> Cylinder::compute()
	{
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

		}
		std::vector<std::vector<Point>> r;
		r.push_back(top);
		r.push_back(down);
		return r;
	}

	void Cylinder::draw(bool debug) {

		std::vector<std::vector<Point>> r = compute();
		std::vector<Point> top=r.at(0);
		std::vector<Point> down=r.at(1);

        //Face down
        glBegin(GL_LINE_STRIP);
        {
            for(int i=0;i<meridians;++i)
				glVertex3d(down.at(i).getX(), down.at(i).getY(), down.at(i).getZ());

			glVertex3d(down.at(0).getX(), down.at(0).getY(), down.at(0).getZ());
        }
        glEnd();


		glBegin(GL_TRIANGLE_STRIP);
		{
			for(int i=0;i< meridians;++i) {

				glVertex3d(top.at(i).getX(), top.at(i).getY(), top.at(i).getZ());
				glVertex3d(down.at(i).getX(), down.at(i).getY(), down.at(i).getZ());
			}
			glVertex3d(top.at(0).getX(), top.at(0).getY(), top.at(0).getZ());
			glVertex3d(down.at(0).getX(), down.at(0).getY(), down.at(0).getZ());


		}
		glEnd();
	}

	double Cylinder::equation(const Point &point)
	{
		double powCenter = pow(point.getX(), 2) + pow(point.getY(), 2) + pow(point.getZ(), 2);
		double powCylinderAxe = pow(Vector::RIGHT.getX(), 2) + pow(Vector::RIGHT.getY(), 2) + pow(Vector::RIGHT.getZ(), 2);
		Vector v(Vector::RIGHT);
		v.setX(v.getX() * point.getX());
		v.setY(v.getY() * point.getY());
		v.setZ(v.getZ() * point.getZ());
		double centerMulti = pow(v.getX() + v.getX() + v.getZ(), 2);
		double division = centerMulti / powCylinderAxe;
		double minus = powCenter - division;
		double powR = pow(rayon, 2);
		return minus - powR;
	}

	void Cylinder::setMeridians(int meridians) {
		this->meridians = meridians;
	}

	int Cylinder::getMeridians() const {
		return meridians;
	}
}
