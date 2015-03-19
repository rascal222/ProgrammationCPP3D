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

		//MERIDIAN 0
		if(debug) {
			glDisable(GL_LIGHTING);
			for(int i=0;i<matrix.at(0).size();++i)
			{
				glColor3f(1.0f, 0.0f, 1.0f);
				glBegin(GL_LINE_STRIP);
				glPoint(north.toCartesian());
				for (int k = 0; k < matrix.size(); ++k) {
					glPoint(matrix.at(k).at(i));
				}
				glPoint(south.toCartesian());
				glEnd();
			}
		}


	}

    float Voxel::equation(const Point& point)
    {
        float sum = pow(point.getX() - center.getX(), 2) + pow(point.getY() - center.getY(), 2) + pow(point.getZ() - center.getZ(), 2);
		float rCarre = pow(rayon, 2);
		return sum - rCarre;
    }
}
