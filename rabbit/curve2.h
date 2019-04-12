#ifndef RABBIT_CURVE2_H
#define RABBIT_CURVE2_H

#include <linalg.h>
#include <rabbit/pntvec.h>

#include <nos/print.h>

namespace rabbit 
{
	template <class T>
	struct curve2 
	{
		virtual pnt2<T> d0(T t) = 0;
		virtual vec2<T> d1(T t) = 0;
	};

	template <class T>
	struct line2 : public curve2<T>
	{
		pnt2<T> 	c;
		vec2<T> 	v;

		line2(pnt<T,2> c, vec<T,2> v) : c(c), v(v) {}

		pnt2<T> d0(T t) override
		{			
			return c + v*t; 
		}

		vec2<T> d1(T t) override
		{			
			return v; 
		}

	};


	template <class T>
	struct circ2 : public curve2<T>
	{
		pnt<T,2> 	c;
		vec<T,2> 	x;
		vec<T,2> 	y;
		
		circ2(pnt2<T> c, vec2<T> x) : c(c), x(x), y(ort(x)) {}
		circ2(pnt2<T> c, vec2<T> x, vec2<T> y) : c(c), x(x), y(y) {}
		circ2(const loc3<T>& location, T radius) 
			: c(location.c), x(location.x * radius), y(location.y * radius) {};
		
		pnt2<T> d0(T t) override
		{			
			return c + x*(T)cos(t) + y*(T)sin(t); 
		}

		vec2<T> d1(T t) override
		{			
			return x*(T)sin(t) + y*(T)cos(t); 
		}

		size_t print_to(nos::ostream & o) const 
		{
			return nos::fprint_to(o, "circ2(c:{},x:{},y:{})", c, x, y);
		}
	};
}

#endif