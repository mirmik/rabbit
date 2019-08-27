#ifndef RABBIT_LINALG_H
#define RABBIT_LINALG_H

#include <linalg-v3/linalg.h>
#include <linalg-v3/linalg-ext.h>
#include <nos/fprint.h>

namespace rabbit 
{
	template <class T> class pnt2;
	template <class T> class vec2;

	template <class T>
	class pnt2 : public linalg::vec<T,2>
	{
	public:
		using parent = linalg::vec<T,2>;
		pnt2(const T& _x, const T& _y) : parent{_x,_y} {}
		pnt2(const pnt2& oth) : parent(oth.x, oth.y) {}
		pnt2(pnt2&& oth) : parent(oth.x, oth.y) {}
		pnt2(const parent& oth) : parent(oth.x, oth.y) {}
		pnt2(parent&& oth) : parent(oth.x, oth.y) {}
		
		pnt2 operator +(const vec2<T>& oth);
		
		pnt2 operator +(const parent& oth) = delete;
		pnt2 operator *(const parent& oth) = delete;

		ssize_t print_to(nos::ostream& os) const
		{
			return nos::fprint_to(os, "pnt2({},{})", (T)parent::x, (T)parent::y);
		}
	};

	template <class T>
	class vec2 : public linalg::vec<T,2>
	{
	public:
		using parent = linalg::vec<T,2>;
		vec2(T _x, T _y) : parent{_x,_y} {}
		vec2(const vec2& oth) : parent(oth.x, oth.y) {}
		vec2(vec2&& oth) : parent(oth.x, oth.y) {}
		vec2(const parent& oth) : parent(oth.x, oth.y) {}
		vec2(parent&& oth) : parent(oth.x, oth.y) {}
		
		vec2 operator *(T s) { return ((parent&)(*this)) * s; }
		vec2 operator +(const vec2& oth) { return ((parent&)(*this)) + (parent&)oth; }

		vec2 operator +(const parent& oth) = delete;
		vec2 operator *(const parent& oth) = delete;

		ssize_t print_to(nos::ostream& os) const
		{
			return nos::fprint_to(os, "vec2({},{})", (T)parent::x, (T)parent::y);
		}
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



	template <class T>
	pnt2<T> pnt2<T>::operator +(const vec2<T>& oth) 
	{ 
		return ((parent&)(*this)) + (parent&)oth; 
	}		
}

#endif