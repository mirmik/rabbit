#ifndef RABBIT_GEOM_CURVE_H
#define RABBIT_GEOM_CURVE_H

#include <rabbit/types.h>

namespace rabbit
{
	class curve
	{
	protected:
		pose3 _pose;

	public:
		curve() {};
		curve(pose3 pose) : _pose(pose) {}

		virtual vec3 d0(real t) = 0;
		virtual vec3 d1(real t) = 0;

		virtual real tmin() = 0;
		virtual real tmax() = 0;
	};

	class ellipse_curve : public curve
	{
		real  _a;
		real  _b;

	public:
		ellipse_curve(real a, real b, pose3 pose)
			: _a(a), _b(b), curve(pose)
		{}

		vec3 d0(real t) override
		{
			real x = _a * cos(t);
			real y = _b * sin(t);
			real z = 0;

			return _pose({x, y, z});
		}

		vec3 d1(real t) override
		{
			real x = - _a * sin(t);
			real y =   _b * cos(t);
			real z = 0;

			return _pose({x, y, z});
		}
	};
}

#endif