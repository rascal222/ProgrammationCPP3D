#ifndef PROG_3D_CURVE_HPP_DEFINED
#define PROG_3D_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include "Point.hpp"
#include <vector>

/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

	class Curve {
	private:
		int pointsNumber;
	public:
		Curve();

		Curve(int);

		virtual ~Curve();

		virtual std::vector<Point> compute() = 0;

		virtual void setPointsNumber(int n);

		virtual int getPointsNumber();
	};
}

#endif