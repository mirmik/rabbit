#ifndef RABBIT_SURFACE_H
#define RABBIT_SURFACE_H

#include <rabbit/types.h>
#include <rabbit/space/pose3.h>

namespace rabbit
{
	class surface
	{
	public:
		virtual real umin() = 0;
		virtual real umax() = 0;
		virtual real vmin() = 0;
		virtual real vmax() = 0;

		virtual vec3 value(real u, real v) = 0;
	};

	class sphere_surface : public surface
	{
		real _radius;
		pose3 _pose;

	public:
		sphere_surface(real radius) : _radius(radius), _pose() {}
		sphere_surface(real radius, const pose3 & pose) : _radius(radius), _pose(pose) {}

		vec3 value(real u, real v) override
		{
			real x = _radius * cos(v) * cos(u);
			real y = _radius * cos(v) * sin(u);
			real z = _radius * sin(v);
		
			return _pose(vec3{x,y,z});
		}

		real umin() { return 0; }
		real umax() { return M_PI*2;}
		real vmin() { return -M_PI/2; }
		real vmax() { return M_PI/2; }
	};


	class parabolic_surface : public surface
	{
		real _a, _b;
		pose3 _pose;

	public:
		sphere_surface(real a, real b) : _a(a), _b(b), _pose() {}
		sphere_surface(real a, real b, const pose3 & pose) : _a(a), _pose(pose) {}

		vec3 value(real u, real v) override
		{
			real x = _radius * cos(v) * cos(u);
			real y = _radius * cos(v) * sin(u);
			real z = _radius * sin(v);
		
			return _pose(vec3{x,y,z});
		}

		real umin() { return 0; }
		real umax() { return M_PI*2;}
		real vmin() { return -M_PI/2; }
		real vmax() { return M_PI/2; }
	};
}

#endif