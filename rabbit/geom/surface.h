#ifndef RABBIT_SURFACE_H
#define RABBIT_SURFACE_H

#include <rabbit/types.h>
#include <rabbit/space/pose3.h>

namespace rabbit
{
	class surface
	{
	protected:
		pose3 _pose;

	public:
		surface(){}
		surface(const pose3& pose) : _pose(pose) {}
		virtual ~surface() = default;

		virtual real umin() = 0;
		virtual real umax() = 0;
		virtual real vmin() = 0;
		virtual real vmax() = 0;

		virtual vec3 value(real u, real v) = 0;
	};

	class sphere_surface : public surface
	{
		real _radius;

	public:
		sphere_surface(real radius) : _radius(radius), surface() {}
		sphere_surface(real radius, const pose3 & pose) : _radius(radius), surface(pose) {}

		vec3 value(real u, real v) override
		{
			real x = _radius * cos(v) * cos(u);
			real y = _radius * cos(v) * sin(u);
			real z = _radius * sin(v);

			return _pose(vec3{x, y, z});
		}

		real umin() { return 0; }
		real umax() { return M_PI * 2;}
		real vmin() { return -M_PI / 2; }
		real vmax() { return M_PI / 2; }
	};


	class parabolic_surface : public surface
	{
		real _a, _b;

	public:
		parabolic_surface(real a, real b) : _a(a), _b(b), surface() {}
		parabolic_surface(real a, real b, const pose3 & pose) : _a(a), _b(b), surface(pose) {}

		vec3 value(real u, real v) override
		{
			real x = u;
			real y = v;
			real z = _a * u * u + _b * v * v;

			return _pose(vec3{x, y, z});
		}

		real umin() { return -std::numeric_limits<real>::infinity(); }
		real umax() { return std::numeric_limits<real>::infinity();}
		real vmin() { return -std::numeric_limits<real>::infinity(); }
		real vmax() { return std::numeric_limits<real>::infinity(); }
	};

	class round_parabolic_surface : public surface
	{
		real _a;

	public:
		round_parabolic_surface(real a) : _a(a), surface() {}
		round_parabolic_surface(real a, const pose3 & pose) : _a(a), surface(pose) {}

		vec3 value(real u, real v) override
		{
			real m = _a * sqrt(v);
			real x = m * cos(u);
			real y = m * sin(u);
			real z = v;

			return _pose(vec3{x, y, z});
		}

		real umin() { return 0; }
		real umax() { return 2 * M_PI;}
		real vmin() { return 0; }
		real vmax() { return std::numeric_limits<real>::infinity(); }
	};


	class torus_surface : public surface
	{
		real _r1, _r2;

	public:
		torus_surface(real r1, real r2) : _r1(r1), _r2(r2), surface() {}
		torus_surface(real r1, real r2, const pose3 & pose) :
			_r1(r1), _r2(r2), surface(pose) {}

		vec3 value(real u, real v) override
		{
			real x = (_r1 + _r2*cos(v)) * cos(u);
			real y = (_r1 + _r2*cos(v)) * sin(u);
			real z = _r2 * sin(v);

			return _pose(vec3{x, y, z});
		}

		real umin() { return 0; }
		real umax() { return 2 * M_PI;}
		real vmin() { return -M_PI; }
		real vmax() { return M_PI; }
	};
}

#endif