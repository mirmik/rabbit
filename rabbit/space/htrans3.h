#ifndef RABBIT_TRANS2_H
#define RABBIT_TRANS2_H

#include <rabbit/space/screw.h>
#include <rabbit/linalg.h>

namespace rabbit
{
	using linalg::ostream_overloads::operator <<;

	template <typename T>
	struct htrans3
	{
		linalg::vec<T, 4> ang;
		linalg::vec<T, 3> lin;

		htrans3() : ang{0, 0, 0, 1}, lin{0, 0, 0} {}
		htrans3(
		    const linalg::vec<T, 4>& q,
		    const linalg::vec<T, 3>& l
		)
			: ang(q), lin(l)
		{}

		linalg::vec<T, 3> rotate(linalg::vec<T, 3> vec) const
		{
			return linalg::qrot(ang, vec);
		};

/*		screw2<T> rotate_screw(screw2<T> scr)
		{
			return { scr.ang, linalg::rot(orient, scr.lin) };
		};*/

		htrans3 operator * (const htrans3& oth)
		{
			return htrans3(
			           linalg::qmul(ang, oth.ang),
			           linalg::qrot(ang, oth.lin) + lin
			       );
		}

		bool operator == (const htrans3& oth) const
		{
			return lin == oth.lin && ang == oth.ang;
		}

		/*
		// В 2д пространстве сложение с бивектором аналогично
		// композиции трансформаций.
		// !!! Скорее всего в обратном порядке!!!
		// Разность выполняется в общем базисе. Композиция
		// В базисе левого объекта.

		screw2<T> operator - (const htrans2<T>& oth)
		{
			//PRINT(*this);
			//PRINT(oth);

			return { orient - oth.orient,
			         //linalg::rot(-oth.orient, center - oth.center)
			         center - oth.center
			     };
		}

		htrans2 integrate_speed(const screw2<T>& spd, T delta)
		{
			return *this + spd * delta;
		}*/

		htrans3 inverse()
		{
			auto inv_q = linalg::qinv(ang);

			return
			{
				inv_q,
				linalg::qrot(inv_q, -lin)
			};
		}

		screw<T, 3> to_screw() const
		{
			auto axis = linalg::qaxis(ang);
			auto angle = linalg::qangle(ang);

			if (angle == 0) 
			{
				axis = {0,0,0};	
			}

			return
			{
				axis * angle,
				lin
			};
		}

		/*linalg::vec<T,2> rotate(const linalg::vec<T,2>& v)
		{
			return linalg::rot(orient, v);
		}

		rabbit::screw<T,2> rotate(const rabbit::screw<T,2>& v)
		{
			return {v.ang, linalg::rot(orient, v.lin)};
		}

		linalg::vec<T,2> inverse_rotate(const linalg::vec<T,2>& v)
		{
			return linalg::rot(-orient, v);
		}

		T rotation() { return orient; }

		linalg::vec<T, 2> translation() { return center; }*/

		ssize_t print_to(nos::ostream& out) const
		{
			return nos::fprint_to(out, "htrans({},{})", ang, lin);
		}
	};

	template<class C, class T>
	std::basic_ostream<C> & operator << (
	    std::basic_ostream<C> & out,
	    const rabbit::htrans3<T> & tr)
	{
		return out << '{' << tr.ang << ',' << tr.lin << '}';
	}
}

#endif