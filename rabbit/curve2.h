#ifndef RABBIT_GEOM_CURVE2_H
#define RABBIT_GEOM_CURVE2_H

#include <rabbit/linalg.h>
#include <rabbit/interval.h>

#include <nos/print.h>
#include <nos/fprint.h>

#include <utility>

namespace rabbit
{
	namespace crv2
	{
		class curve2
		{
		public:
			virtual vec2 d0(r_float t) = 0;
			virtual vec2 d1(r_float t) = 0;

			r_float strt = -std::numeric_limits<r_float>::infinity();
			r_float fini =  std::numeric_limits<r_float>::infinity();
			bool periodic = false; 
		};

		class line : public curve2
		{
			vec2 loc;
			vec2 dir;

			line(vec2 loc, vec2 dir)
				: loc(loc), dir(dir)
			{}

			static line segment(vec2 apnt, vec2 bpnt) 
			{
				auto diff = bpnt - apnt;
				auto ln = line(apnt, normalize(diff));

				ln.strt = 0;
				ln.fini = length(diff);

				return ln;
			}

			vec2 d0(r_float t) override
			{
				return loc + dir * t;
			}

			vec2 d1(r_float t) override
			{
				(void) t;
				return dir;
			}
		};

		struct trimmed_curve 
		{

		};

		/*template <class T>
		struct ellipse_curve2 : public curve2<T>
		{
			rabbit::pnt2<T> 	c;
			rabbit::vec2<T> 	x;
			rabbit::vec2<T> 	y;

			ellipse_curve2(
			    rabbit::vec2<T> c,
			    rabbit::vec2<T> x)
				:
				c(c), x(x), y(ort(x))
			{}

			ellipse_curve2(
			    rabbit::pnt2<T> _c,
			    rabbit::vec2<T> _x,
			    rabbit::vec2<T> _y)
				:
				c(_c), x(_x), y(_y)
			{
				/*PRINT(c);
				PRINT(_c);
				PRINT(y);
				PRINT(_y);*/
		/*	}

			rabbit::pnt2<T> d0(T t) override
			{
				//PRINT(x);
				//PRINT(y);
				//PRINT(c);
				return c + x * (T)cos(t) + y * (T)sin(t);
			}

			rabbit::vec2<T> d1(T t) override
			{
				return x * (T)sin(t) + y * (T)cos(t);
			}

			template <class Trans>
			ellipse_curve2 transform(const Trans& trans)
			{
				return ellipse_curve2
				{
					trans.transform(c),
					trans.rotate(x),
					trans.rotate(y)
				};
			}

			template <class Trans>
			ellipse_curve2 self_transform(const Trans& trans)
			{
				c = trans.transform(c);
				x = trans.rotate(x);
				y = trans.rotate(y);
			}

			size_t print_to(nos::ostream & o) const
			{
				return nos::fprint_to(o, "ellipse2(c:{},x:{},y:{})", c, x, y);
			}
		};

		template <class T>
		struct bounded_curve2 : public curve2<T>
		{
			virtual T tstart() = 0;
			virtual T tfinish() = 0;

			virtual T tlength() { return tfinish() - tstart(); }
		};

		template <class T>
		struct segment2 : public bounded_curve2<T>
		{
			pnt2<T> 	a;
			pnt2<T> 	b;

			pnt2<T> d0(T t) override { return a * (1 - t) + b * t; }
			vec2<T> d1(T t) override { return b - a; }

			T tstart() override  { return 0; }
			T tfinish() override { return 1; }
			T tlength() override { return 1; }
		};

		template <class T>
		struct trimmed_curve2 : public bounded_curve2<T>
		{
			curve2<T> * base;
			rabbit::interval<T> interval;

			pnt2<T> d0(T t) override { return base->d0(t); }
			vec2<T> d1(T t) override { return base->d1(t); }

			T tstart() override  { return interval.minimum; }
			T tfinish() override { return interval.maximum; }
			trimmed_curve2(curve2<T> * base, T a, T b) : base(base), interval(a, b) {}
		};
	}*/
	}
}

#endif