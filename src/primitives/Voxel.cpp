#include "Voxel.hpp"
#include <GL/gl.h>
#include "../glWrappers/GlCoreRendering.hpp"
#include <iostream>

namespace prog_3D
{
	Voxel::Voxel(const Point &center, double rayon) : center(center), length(rayon) {

	}

	Voxel::~Voxel() {
	}


	double Voxel::getLength() const {
		return length;
	}


	std::vector<Point> Voxel::getVertices() const {
		std::vector<Point> _cached;

		//-x,-y,-z
		Point p;
		p.set(
				getCenter().getX() - (0.5 * getLength()),
				getCenter().getY() - (0.5 * getLength()),
				getCenter().getZ() - (0.5 * getLength())
		);
		_cached.push_back(p);
		//+x,-y,-z
		p.set(
				getCenter().getX() + (0.5 * getLength()),
				getCenter().getY() - (0.5 * getLength()),
				getCenter().getZ() - (0.5 * getLength())
		);
		_cached.push_back(p);
		//+x,+y,-z
		p.set(
				getCenter().getX() + (0.5 * getLength()),
				getCenter().getY() + (0.5 * getLength()),
				getCenter().getZ() - (0.5 * getLength())
		);
		_cached.push_back(p);
		//-x,+y,-z
		p.set(
				getCenter().getX() - (0.5 * getLength()),
				getCenter().getY() + (0.5 * getLength()),
				getCenter().getZ() - (0.5 * getLength())
		);
		_cached.push_back(p);
		//-x,-y,+z
		p.set(
				getCenter().getX() - (0.5 * getLength()),
				getCenter().getY() - (0.5 * getLength()),
				getCenter().getZ() + (0.5 * getLength())
		);
		_cached.push_back(p);
		//+x,-y,+z
		p.set(
				getCenter().getX() + (0.5 * getLength()),
				getCenter().getY() - (0.5 * getLength()),
				getCenter().getZ() + (0.5 * getLength())
		);
		_cached.push_back(p);
		p.set(
				getCenter().getX() + (0.5 * getLength()),
				getCenter().getY() + (0.5 * getLength()),
				getCenter().getZ() + (0.5 * getLength())
		);
		_cached.push_back(p);
		p.set(
				getCenter().getX() - (0.5 * getLength()),
				getCenter().getY() + (0.5 * getLength()),
				getCenter().getZ() + (0.5 * getLength())
		);
		_cached.push_back(p);
		return _cached;
	}


	void Voxel::draw(bool debug, bool fill) {
		std::vector<Point> _cached = getVertices();
		if (debug) {
			for (int i = 0; i < 8; ++i)
				drawPoint(_cached[i]);
			drawPoint(getCenter());
		}


		if (fill) {
			if (debug)
				glColor3f(1.0f, 0.0f, .0f);
			//LEFT FACE z-1 (RED)
			fillTriangle(_cached[3], _cached[0], _cached[4]);
			fillTriangle(_cached[7], _cached[3], _cached[4]);


			//BACK FACE x-1 (YELLOW)
			if (debug)
				glColor3f(1.0f, 1.0f, .0f);

			fillTriangle(_cached[3], _cached[1], _cached[0]);
			fillTriangle(_cached[3], _cached[2], _cached[1]);

			//TOP FACE y+1 (WHITE)
			if (debug)
				glColor3f(1.0f, 1.0f, 1.0f);
			fillTriangle(_cached[7], _cached[2], _cached[3]);
			fillTriangle(_cached[7], _cached[6], _cached[2]);

			//BOTTOM FACE y-1 (PINK)
			if (debug)
				glColor3f(1.0f, 0.0f, 1.0f);
			fillTriangle(_cached[0], _cached[1], _cached[4]);
			fillTriangle(_cached[1], _cached[5], _cached[4]);

			//RIGHT FACE z+1 (GREEN)
			if (debug)
				glColor3f(.0f, 1.0f, .0f);
			fillTriangle(_cached[1], _cached[2], _cached[5]);
			fillTriangle(_cached[2], _cached[6], _cached[5]);

			//TOP FACE x+1 (CYAN)
			if (debug)
				glColor3f(.0f, 1.0f, 1.0f);
			fillTriangle(_cached[4], _cached[5], _cached[6]);
			fillTriangle(_cached[6], _cached[7], _cached[4]);
		}
		else {
			if (debug)
				glColor3f(.0f, 1.0f, 1.0f);
			wireframeSquare(_cached[4], _cached[5], _cached[6], _cached[7]);
			if (debug)
				glColor3f(.0f, 1.0f, .0f);
			wireframeSquare(_cached[1], _cached[2], _cached[6], _cached[5]);
			if (debug)
				glColor3f(1.0f, 0.0f, 1.0f);
			wireframeSquare(_cached[0], _cached[1], _cached[5], _cached[4]);
			if (debug)
				glColor3f(1.0f, 1.0f, 1.0f);
			wireframeSquare(_cached[7], _cached[6], _cached[2], _cached[3]);
			if (debug)
				glColor3f(1.0f, 1.0f, .0f);
			wireframeSquare(_cached[3], _cached[2], _cached[1], _cached[0]);
			if (debug)
				glColor3f(1.0f, 0.0f, .0f);
			wireframeSquare(_cached[7], _cached[3], _cached[0], _cached[4]);
		}
	}


	std::vector<Voxel> Voxel::cut() {

		std::vector<Voxel> cut;
		for (int i = -1; i < 2; i += 2) {
			for (int j = -1; j < 2; j += 2) {
				for (int k = -1; k < 2; k += 2) {
					Point centerPoint;
					centerPoint.set(
							getCenter().getX() + ((double) k * 0.25 * getLength()),
							getCenter().getY() + ((double) j * 0.25 * getLength()),
							getCenter().getZ() + ((double) i * 0.25 * getLength())
					);
					Voxel voxel(centerPoint, getLength() / 2.0);
					cut.push_back(voxel);
				}
			}
		}

		return cut;
	}

	const Point &Voxel::getCenter() const {
		return center;
	}

	bool Voxel::inVoxel(Point &point) {

		double x_min,y_min,z_min,x_max,y_max,z_max;
		std::vector<Point> vertices = getVertices();
		x_min = vertices.at(0).getX();
		x_max = vertices.at(0).getX();
		y_min = vertices.at(0).getY();
		y_max = vertices.at(0).getY();
		z_min = vertices.at(0).getZ();
		z_max = vertices.at(0).getZ();

		for(Point p : vertices) {
			if(p.getX()<= x_min)
				x_min = p.getX();
			if(p.getX() >= x_max)
				x_max = p.getX();
			if(p.getY()<= y_min)
				y_min = p.getY();
			if(p.getY() >= y_max)
				y_max = p.getY();
			if(p.getZ()<= z_min)
				z_min = p.getZ();
			if(p.getZ() >= z_max)
				z_max = p.getZ();
		}

		return x_min <= point.getX() <= x_max
			   && y_min <= point.getY() <= y_max
			   && z_min <= point.getZ() <= z_max;
	}
}
