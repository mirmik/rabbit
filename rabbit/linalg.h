#ifndef RABBIT_LINALG_H
#define RABBIT_LINALG_H

#include <linalg-v3/linalg.h>

namespace rabbit 
{
	template <class T>
	class pnt2 : public linalg::vec<T,2>
	{
	public:
		using parent = linalg::vec<T,2>;
		pnt2(T x, T y) : parent(x,y) {}
		pnt2(const parent& oth) : parent(oth) {}
		
		pnt2 operator +(const parent& oth) { return ((parent&)(*this)) + oth; }	
	};

	template <class T>
	class vec2 : public linalg::vec<T,2>
	{
	public:
		using parent = linalg::vec<T,2>;
		vec2(T x, T y) : parent(x,y) {}
		vec2(const parent& oth) : parent(oth) {}

		vec2 operator *(T s) { return ((parent&)(*this)) * s; }
		vec2 operator +(const parent& oth) { return ((parent&)(*this)) + oth; }
	};

	template <class T>
	class dir2 : public linalg::vec<T,2>
	{

	};

	template <class T>
	class pnt3 : linalg::vec<T,3>
	{

	};

	template <class T>
	class vec3 : linalg::vec<T,3>
	{

	};

	template <class T>
	class dir3 : linalg::vec<T,3>
	{

	};
}

#endif