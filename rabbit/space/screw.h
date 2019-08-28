#ifndef RABBIT_SPACE_SCREW_H
#define RABBIT_SPACE_SCREW_H

#include <linalg-v3/linalg.h>

namespace rabbit 
{
	template< class T, int N >
	struct screw;

	template <class T>
	using screw2 = screw<T,2>;

	template <class T>
	using screw3 = screw<T,3>;

	template <class T>
	struct screw<T,3> 
	{
		linalg::vec<T,3> ang;
		linalg::vec<T,3> lin;

		screw(const linalg::vec<T,3>& ang, const linalg::vec<T,3>& lin);

		screw operator * (float koeff) 
		{
			return { ang * koeff, lin * koeff };
		}

		T rotation() { return ang; }
		linalg::vec<T,3> translation() { return lin; }
	};

	template <class T>
	struct screw<T,2>
	{
		T ang;
		linalg::vec<T,2> lin;

		screw(T ang, const linalg::vec<T,2>& lin) : ang(ang), lin(lin) {}
		screw(){}

		screw operator * (float koeff) 
		{
			return { ang * koeff, lin * koeff };
		}

		T rotation() { return ang; }
		linalg::vec<T,2> translation() { return lin; }

		T norm() const { return sqrt(ang * ang + lin.x * lin.x + lin.y * lin.y); }

		T dot(const screw& o) { return ang*o.ang + lin.x*o.lin.x + lin.y*o.lin.y; } 
	};

	template<class T, int N> 
	screw<T,N> operator - (const screw<T,N>& a, const screw<T,N>& b) 
	{ return { a.ang - b.ang, a.lin - b.lin }; }

	template<class T, int N> 
	screw<T,N> operator + (const screw<T,N>& a, const screw<T,N>& b) 
	{ return { a.ang + b.ang, a.lin + b.lin }; }

	template<class T, int N> 
	screw<T,N>& operator += (screw<T,N>& a, const screw<T,N>& b) 
	{ 
		a.ang += b.ang; 
		a.lin += b.lin; 
		return a;
	}

	template<class T, int N, class O> 
	screw<T,N> operator / (const screw<T,N>& a, const O& b) 
	{ return { a.ang / b, a.lin / b }; }

	template<class T, int N, class O> 
	screw<T,N> operator * (const O& b, const screw<T,N>& a) 
	{ return { b * a.ang, b * a.lin }; }

	template<class C, class T, int N>
		std::basic_ostream<C> & operator << (
		    std::basic_ostream<C> & out,
		    const rabbit::screw<T,N> & tr)
		{
			return out << '{' << tr.ang << ',' << tr.lin << '}';
		}
}

#endif