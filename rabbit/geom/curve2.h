#ifndef RABBIT_GEOM_CURVE2_H
#define RABBIT_GEOM_CURVE2_H

#include <rabbit/linalg.h>
#include <rabbit/interval.h>

#include <nos/print.h>
#include <nos/fprint.h>

namespace rabbit
{
	template <class T>
	struct curve2
	{
		virtual rabbit::pnt2<T> d0(T t) = 0;
		virtual rabbit::vec2<T> d1(T t) = 0;
	};

	template <class T>
	struct line_curve2 : public curve2<T>
	{
		rabbit::pnt2<T> 	c;
		rabbit::dir2<T> 	d;

		line_curve2(
		    rabbit::pnt2<T> c,
		    rabbit::dir2<T> d)
			:
			c(c), d(d)
		{}

		rabbit::pnt2<T> d0(T t) override
		{
			return c + d * t;
		}

		rabbit::vec2<T> d1(T t) override
		{
			(void) t;
			return d;
		}

	};

	template <class T>
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
			PRINT(c);
			PRINT(_c);
			PRINT(y);
			PRINT(_y);
		}

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
		trimmed_curve2(curve2<T> * base, T a, T b) : base(base), interval(a,b) {}
	};
}

#endif