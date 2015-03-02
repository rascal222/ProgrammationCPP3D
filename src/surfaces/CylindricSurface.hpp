#ifndef CYLINDRIC_SURFACE_HPP_DEFINED
#define CYLINDRIC_SURFACE_HPP_DEFINED


#include "../core/Axis.hpp"
#include "../core/Curve.hpp"
#include "../core/Point.hpp"
#include "Surface.hpp"
#include <memory>

namespace prog_3D
{

	class CylindricSurface: public virtual prog_3D::Surface {
	private:
		std::shared_ptr<Axis> director;
		std::shared_ptr<Curve> generator;
	public:
		CylindricSurface(std::shared_ptr<Axis>, std::shared_ptr<Curve>);
		CylindricSurface(std::shared_ptr<Axis> direct, std::shared_ptr<Curve> g,int nbU,int nbV);

		virtual ~CylindricSurface();

		std::shared_ptr<Axis> getDirector();

		std::shared_ptr<Curve> getGenerator();

		virtual Point compute(double u, double v);

		virtual std::vector<std::vector<Point>> compute();

		virtual void draw();
		virtual void draw(bool);

	};
}
#endif