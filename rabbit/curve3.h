#ifndef RABBIT_CURVE3_H
#define RABBIT_CURVE3_H

#include <linalg.h>
#include <rabbit/pntvec.h>

#include <nos/print.h>

namespace rabbit 
{
	template <class T>
	struct curve3 
	{
		virtual pnt3<T> d0(T t) = 0;
		virtual vec3<T> d1(T t) = 0;
	};

	template <class T>
	struct line3 : public curve3<T>
	{
		pnt3<T> 	c;
		vec3<T> 	v;

		line3(pnt3<T> c, vec3<T> v) : c(c), v(v) {}

		pnt3<T> d0(T t) override
		{			
			return c + v*t; 
		}

		vec3<T> d1(T t) override
		{			
			return v; 
		}

	};


	template <class T>
	struct circ3 : public curve2<T>
	{
		pnt3<T> 	c;
		vec3<T> 	x;
		vec3<T> 	y;
		
		circ3(pnt3<T> c, vec3<T> x, vec3<T> y) : c(c), x(x), y(y) {}
		
		pnt3<T> d0(T t) override
		{			
			return c + x*(T)cos(t) + y*(T)sin(t); 
		}

		vec3<T> d1(T t) override
		{			
			return x*(T)sin(t) + y*(T)cos(t); 
		}

		size_t print_to(nos::ostream & o) const 
		{
			return nos::fprint_to(o, "circ3(c:{},x:{},y:{})", c, x, y);
		}
	};
}

#endif