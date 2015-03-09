#include "Sphere.hpp"
#include "../core/Point.hpp"
#include "../core/PolarPoint.hpp"
#include "../core/GlCoreRendering.hpp"
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <iostream>
namespace prog_3D {

	Sphere::Sphere() {
		center = Point::Origin;
		rayon = 1.0f;
		paralleles = 10;
		meridians = 10;
	}

	Sphere::Sphere(float rayon, int paralleles,int meridians, Point& center)
	{
		this->center = center;
		this->rayon=rayon;
		this->paralleles=paralleles;
		this->meridians=meridians;
	}

	Sphere::~Sphere()
	{
	}

	void Sphere::draw() {
		draw(false);
	}

	void Sphere::draw(bool debug) {

		std::vector<std::vector<Point>> matrix;

		PolarPoint north(center,0,0,rayon);
		PolarPoint south(center,M_PI,M_PI,rayon);
		drawPoint(north.toCartesian());
		glColor3f(0.0f, 1.0f, 0.0f);
		drawPoint(south.toCartesian());
		glColor3f(1.0f,0.0f,0.0f);
//		for(int j=0;j < paralleles ;++j)
//		{
//			std::vector<Point> down;
//			double angleG = M_PI * j / paralleles;
//			for (int i = 1; i < meridians; ++i)
//			{
//				double angle = 2 * M_PI * i / meridians;
//
//				PolarPoint p(center, angleG, angle, rayon);
//				down.push_back(p.toCartesian());
//			}
//			matrix.push_back(down);
//		}


		for (int i = 1; i < meridians-1; ++i)
		{
			std::vector<Point> down;
			double angle =  (double) (M_PI * i) /(double) (meridians-1.0);
			if(debug)
				glBegin(GL_LINE_STRIP);
			for(int j=0;j < paralleles-1;++j)
			{
				double angleG = ((double) (2*M_PI * j) / (double) (paralleles-1.0));
				PolarPoint p(center, angleG,angle, rayon);
				down.push_back(p.toCartesian());
				if(debug)
					glPoint(p.toCartesian());
			}
			if(debug)
				glPoint(down.at(0));
			glEnd();
			matrix.push_back(down);
		}


		//MERIDIAN 0
		if(debug) {
			glColor3f(1.0f, 0.0f, 1.0f);
			glBegin(GL_LINE_STRIP);
			glPoint(north.toCartesian());
			for (int k = 0; k < matrix.size(); ++k) {
				glPoint(matrix.at(k).at(0));
			}
			glPoint(south.toCartesian());
			glEnd();
		}

		//NORTH POLE
		glBegin(GL_TRIANGLE_FAN);
		glPoint(north.toCartesian());
		for(int k=0;k<matrix.at(0).size();++k)
		{
			glPoint(matrix.at(0).at(k));
		}
		glPoint(matrix.at(0).at(0));
		glEnd();

		//SOUTH POLE

		glBegin(GL_TRIANGLE_FAN);
		glPoint(south.toCartesian());
		for(int k=0;k<matrix.at(matrix.size()-1).size();++k)
		{
			glPoint(matrix.at(matrix.size()-1).at(k));
		}
		glPoint(matrix.at(matrix.size()-1).at(0));
		glEnd();



		for(int i=0;i<matrix.at(0).size()-1;++i)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for (int k = 0; k < matrix.size(); ++k)
			{
				glPoint(matrix.at(k).at(i));
				glPoint(matrix.at(k).at((i+1)));
			}
			glEnd();
		}

		glBegin(GL_TRIANGLE_STRIP);
		for (int k = 0; k < matrix.size(); ++k)
		{
			glPoint(matrix.at(k).at(matrix.at(0).size()-1));
			glPoint(matrix.at(k).at((0)));
		}
		glEnd();





	}
}