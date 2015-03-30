#include "Sphere.hpp"
#include "../core/PolarPoint.hpp"
#include "../glWrappers/GlCoreRendering.hpp"
#include <cmath>
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

	std::vector<std::vector<Point>> Sphere::compute()
	{
		std::vector<std::vector<Point>> matrix;
		PolarPoint north(center,0,0,rayon);
		PolarPoint south(center,M_PI,M_PI,rayon);
		std::vector<Point> vnorth;
		std::vector<Point> vsouth;
		vnorth.push_back(north.toCartesian());

		for (int i = 1; i < meridians-1; ++i)
		{
			std::vector<Point> down;
			double angle =  (double) (M_PI * i) /(double) (meridians-1.0);
			for(int j=0;j < paralleles-1;++j)
			{
				double angleG = ((double) (2*M_PI * j) / (double) (paralleles-1.0));
				PolarPoint p(center, angleG,angle, rayon);
				down.push_back(p.toCartesian());
			}
			matrix.push_back(down);
		}
		vsouth.push_back(south.toCartesian());
		return matrix;
	}


	void Sphere::draw(bool debug) {

		std::vector<std::vector<Point>> matrix = compute();
		Point north = matrix.at(0).at(0);
		Point south = matrix.at(matrix.size()-1).at(0);
		int LightPos[4] = {0, 0, 0, 1};
		int MatSpec [4] = {1,1,1,1};
		glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		LightPos[0] = 0;
		LightPos[1] = 2;
		LightPos[2] = 2;
		glLightiv(GL_LIGHT0, GL_POSITION, LightPos);
		float LightDif[4] = {0.f, 1.f, 1.f, 1.f};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .05f);
		GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

		glColor3f(1.0f,1.0f,1.0f);
		//NORTH POLE
		glBegin(GL_TRIANGLE_FAN);
		glPoint(matrix.at(0).at(0));
		for(int k=0;k<matrix.at(1).size();++k)
		{
			glPoint(matrix.at(1).at(k));
		}
		glPoint(matrix.at(1).at(0));
		glEnd();

		//SOUTH POLE
		glBegin(GL_TRIANGLE_FAN);
		glPoint(matrix.at(matrix.size()-1).at(0));
		for(int k=0;k<matrix.at(matrix.size()-2).size();++k)
		{
			glPoint(matrix.at(matrix.size()-2).at(k));
		}
		glPoint(matrix.at(matrix.size()-2).at(0));
		glEnd();

		for(unsigned int i=0;i<matrix.at(1).size()-1;++i)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for (unsigned int k = 1; k < matrix.size()-1; ++k)
			{
				glPoint(matrix.at(k).at(i));
				glPoint(matrix.at(k).at((i+1)));
			}
			glEnd();
		}
		glBegin(GL_TRIANGLE_STRIP);
		for (unsigned int k = 1; k < matrix.size()-1; ++k)
		{
			glPoint(matrix.at(k).at(matrix.at(1).size()-1));
			glPoint(matrix.at(k).at((0)));
		}
		glEnd();
	}

	double Sphere::equation(const Point &point)
    {
		double sum = pow(point.getX() - center.getX(), 2)
				+ pow(point.getY() - center.getY(), 2)
				+ pow(point.getZ() - center.getZ(), 2);
		double rCarre = pow(rayon, 2);
		return sum - rCarre;
    }
}
