#ifndef RABBIT_PNTVEC_H
#define RABBIT_PNTVEC_H

#include <linalg.h>

namespace rabbit 
{
	template <typename T, int N> using vec = linalg::vec<T,N>;

	template <typename T, int N> 
	struct pnt : public linalg::vec<T,N> 
	{
		using parent = linalg::vec<T,N>;

		template<class ... Args> pnt(Args&& ... args) 
			: parent(std::forward<Args>(args) ...) {}
	};

	template <typename T, int N> pnt<T,N> operator-(const pnt<T,N>& a, const vec<T,N>& b) 
	{ return static_cast<const linalg::vec<T,N>&>(a) - static_cast<const linalg::vec<T,N>&>(b); }
	
	template <typename T, int N> pnt<T,N> operator+(const pnt<T,N>& a, const vec<T,N>& b) 
	{ return static_cast<const linalg::vec<T,N>&>(a) - static_cast<const linalg::vec<T,N>&>(b); }

	template <class T> vec<T, 2> ort(vec<T, 2> a) 
	{ 
		return {-a.y, a.x}; 
	}

	template <typename T, int N> 
	struct uvec : public linalg::vec<T,N>
	{
		using parent = linalg::vec<T,N>;

		uvec(const uvec& oth) : parent(oth) {} 

		template<class ... Args> uvec(Args&& ... args) 
			: parent(std::forward<Args>(args) ...) 
		{
			auto l = length(*this);
			for (auto& a: *this) { a /= l; }
		}
	};

	template <typename T> using pnt2 = pnt<T,2>;
	template <typename T> using pnt3 = pnt<T,3>;

	template <typename T> using vec2 = vec<T,2>;
	template <typename T> using vec3 = vec<T,3>;

	template <typename T> using uvec2 = uvec<T,2>;
	template <typename T> using uvec3 = uvec<T,3>;

	template <class T>
	struct loc3 
	{
		pnt3<T> c;
		uvec3<T> x;
		uvec3<T> y;
	};
}

#endif