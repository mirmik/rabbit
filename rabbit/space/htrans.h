#ifndef RABBIT_TRANS2_H
#define RABBIT_TRANS2_H

#include <linalg.h>
#include <linalg-ext.h>

namespace rabbit
{
	using linalg::ostream_overloads::operator <<;

	template <typename T>
	struct htrans2
	{
		T orient;
		linalg::vec<T,2> center;

		trans2() : orient(0), center{0, 0} {}
		trans2(T rotate_, linalg::vec<T,2> translate_)
			: orient(rotate_), center(translate_) 
		{}

		linalg::vec<T,2> operator()(linalg::vec<T,2> vec)
		{
			return linalg::rot(orient, vec) + center;
		};

		trans2 operator * (const trans2& oth)
		{
			return trans2(
				orient * oth.orient, 
				linalg::rot(orient, oth.center) + center);
		}

		// В 2д пространстве сложение с винтом аналогично 
		// композиции трансформаций.
		trans2 operator + (const screw2<T>& screw) 
		{
			return trans2(
				orient * screw.orient, 
				linalg::rot(orient, screw.center) + center);
		}

		htrans2 integrate(const hspeed2<T>& spd, T delta) 
		{
			return { *this + spd * delta; }
		}
	};

	template<class C, class T>
	std::basic_ostream<C> & operator << (std::basic_ostream<C> & out, const rabbit::trans2<T> & tr)
	{
		return out << '{' << tr.orient << ',' << tr.center << '}';
	}
}

#endif