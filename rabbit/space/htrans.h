#ifndef RABBIT_TRANS2_H
#define RABBIT_TRANS2_H

#include <rabbit/space/hscrew.h>
#include <linalg.h>
#include <linalg-ext.h>

namespace rabbit
{
	using linalg::ostream_overloads::operator <<;

	template <typename T>
	struct htrans2
	{
		T orient;
		linalg::vec<T, 2> center;

		htrans2() : orient(0), center{0, 0} {}
		htrans2(T rotate_, linalg::vec<T, 2> translate_)
			: orient(rotate_), center(translate_)
		{}

		linalg::vec<T, 2> operator()(linalg::vec<T, 2> vec)
		{
			return linalg::rot(orient, vec) + center;
		};

		htrans2 operator * (const htrans2& oth)
		{
			return htrans2(
			           orient + oth.orient,
			           linalg::rot(orient, oth.center) + center);
		}

		// В 2д пространстве сложение с бивектором аналогично
		// композиции трансформаций.
		htrans2 operator + (const screw2<T>& screw)
		{
			return htrans2(
			           orient + screw.orient,
			           linalg::rot(-orient, screw.center) + center);
		}

		htrans2 integrate_speed(const screw2<T>& spd, T delta)
		{
			return *this + spd * delta;
		}
	};

	template<class C, class T>
	std::basic_ostream<C> & operator << (
	    std::basic_ostream<C> & out,
	    const rabbit::htrans2<T> & tr)
	{
		return out << '{' << tr.orient << ',' << tr.center << '}';
	}
}

#endif