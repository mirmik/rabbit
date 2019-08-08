#ifndef RABBIT_GEOM_CURVE2_H
#define RABBIT_GEOM_CURVE2_H

#include <rabbit/linalg.h>

namespace rabbit
{
	template <class T>
	struct curve2
	{
		virtual linalg::vec2<T> d0();
		virtual linalg::vec2<T> d1();
	};

	template <class T>
	struct line_curve2 : public curve
	{
		rabbit::pnt2<T, 2> 	c;
		rabbit::dir2<T, 2> 	d;

		line(
		    linalg::vec<T, 2> a,
		    linalg::vec<T, 2> b)
			:
			a(a), b(b)
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
	struct ellipse_curve2 : public curve
	{
		linalg::vec<T, 2> 	c;
		linalg::vec<T, 2> 	x;
		linalg::vec<T, 2> 	y;

		ellipse_curve2(
		    linalg::vec<T, 2> c,
		    linalg::vec<T, 2> x)
			:
			c(c), x(x), y(ort(x))
		{}

		ellipse_curve2(
		    linalg::vec<T, 2> c,
		    linalg::vec<T, 2> x,
		    linalg::vec<T, 2> y)
			:
			c(c), x(x), y(y)
		{}

		linalg::vec<T, 2> d0(T t) override
		{
			return c + x * (T)cos(t) + y * (T)sin(t);
		}

		linalg::vec<T, 2> d1(T t) override
		{
			return x * (T)sin(t) + y * (T)cos(t);
		}

		template <class Trans>
		ellipse transform(const Trans& trans)
		{
			return ellipse2
			{
				trans.transform(c),
				trans.rotate(x),
				trans.rotate(y)
			}
		}

		size_t print_to(nos::ostream & o) const
		{
			return nos::fprint_to(o, "ellipse2(c:{},x:{},y:{})", c, x, y);
		}
	};

	template <class T>
	struct bounded_curve2
	{
		virtual T tstart();
		virtual T tfinish();

		virtual T tlength() { return finish() - start(); }
	};

	template <class T>
	struct segment2 : public bounded_curve2
	{
		rabbit::pnt2<T, 2> 	a;
		rabbit::pnt2<T, 2> 	b;

		pnt2<T> d0(T t) { return a * (1 - t) + b * t; }
		vec2<T> d1(T t) { return b - a; }
	
		T tstart() override  { return 0; };
		T tfinish() override { return 1; };	
		T tlength() override { return 1; }	
	}

	template <class T>
	struct trimmed_curve2 : public bounded_curve2
	{
		curve * base;
		rabbit::interval interval;

		pnt2<T> d0(T t) { return base->d0(t); }
		vec2<T> d1(T t) { return base->d1(t); }
	}
}

#endif