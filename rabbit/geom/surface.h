#ifndef RABBIT_SURFACE_H
#define RABBIT_SURFACE_H

#include <rabbit/types.h>
#include <ralgo/space/pose3.h>

namespace rabbit
{
	class surface
	{
	protected:
		pose3<real> _pose = {};

	public:
		surface(){}
		surface(const pose3<real>& pose) : _pose(pose) {}
		virtual ~surface() = default;

		virtual real umin() const = 0;
		virtual real umax() const = 0;
		virtual real vmin() const = 0;
		virtual real vmax() const = 0;

		virtual vec3 value(real u, real v) const = 0;
	};

	class sphere_surface : public surface
	{
		real _radius = 0;

	public:
		sphere_surface(real radius) : _radius(radius), surface() {}
		sphere_surface(real radius, const pose3<real> & pose) : _radius(radius), surface(pose) {}

		vec3 value(real u, real v) const override
		{
			real x = _radius * cos(v) * cos(u);
			real y = _radius * cos(v) * sin(u);
			real z = _radius * sin(v);

			return _pose(vec3{x, y, z});
		}

		real umin() const override { return 0; }
		real umax() const override { return M_PI * 2;}
		real vmin() const override { return -M_PI / 2; }
		real vmax() const override { return M_PI / 2; }
	};


	class parabolic_surface : public surface
	{
		real _a=0, _b=0;

	public:
		parabolic_surface(real a, real b) : _a(a), _b(b), surface() {}
		parabolic_surface(real a, real b, const pose3<real> & pose) : _a(a), _b(b), surface(pose) {}

		vec3 value(real u, real v) const override
		{
			real x = u;
			real y = v;
			real z = _a * u * u + _b * v * v;

			return _pose(vec3{x, y, z});
		}

		real umin() const  override { return -std::numeric_limits<real>::infinity(); }
		real umax() const  override { return std::numeric_limits<real>::infinity();}
		real vmin() const  override { return -std::numeric_limits<real>::infinity(); }
		real vmax() const  override { return std::numeric_limits<real>::infinity(); }
	};

	class round_parabolic_surface : public surface
	{
		real _a=0;

	public:
		round_parabolic_surface(real a) : _a(a), surface() {}
		round_parabolic_surface(real a, const pose3<real> & pose) : _a(a), surface(pose) {}

		vec3 value(real u, real v) const override
		{
			real m = _a * sqrt(v);
			real x = m * cos(u);
			real y = m * sin(u);
			real z = v;

			return _pose(vec3{x, y, z});
		}

		real umin() const  override { return 0; }
		real umax() const  override { return 2 * M_PI;}
		real vmin() const  override { return 0; }
		real vmax() const  override { return std::numeric_limits<real>::infinity(); }
	};


	class torus_surface : public surface
	{
		real _r1=0, _r2=0;

	public:
		torus_surface(real r1, real r2) : _r1(r1), _r2(r2), surface() {}
		torus_surface(real r1, real r2, const pose3<real> & pose) :
			_r1(r1), _r2(r2), surface(pose) {}

		vec3 value(real u, real v) const override
		{
			real x = (_r1 + _r2*cos(v)) * cos(u);
			real y = (_r1 + _r2*cos(v)) * sin(u);
			real z = _r2 * sin(v);

			return _pose(vec3{x, y, z});
		}

		real umin() const  override { return 0; }
		real umax() const  override { return 2 * M_PI;}
		real vmin() const  override { return -M_PI; }
		real vmax() const  override { return M_PI; }
	};

	class cylinder_surface : public surface
	{
		real _r=0, _h=0;

	public:
		cylinder_surface(real r, real h) : _r(r), _h(h) {}

		vec3 value(real u, real v) const override
		{
			real x = _r * cos(u);
			real y = _r * sin(u);
			real z = v;

			return _pose(vec3{x, y, z});
		}

		real umin() const  override { return 0; }
		real umax() const  override { return 2 * M_PI;}
		real vmin() const  override { return -std::numeric_limits<float>::infinity(); }
		real vmax() const  override { return std::numeric_limits<float>::infinity(); }
	};
}

#endif