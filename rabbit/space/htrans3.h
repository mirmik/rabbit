#ifndef RABBIT_TRANS2_H
#define RABBIT_TRANS2_H

#include <iostream>

#include <rabbit/space/screw.h>
#include <rabbit/third/linalg.h>

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

		htrans3(
		    const rabbit::screw<T, 3>& scr
		)
			: lin(scr.lin)
		{
			auto w = scr.ang;

			auto angle = length(w);			
			auto axis = w / angle;

			if (angle == 0) 
				ang = {0,0,0,1};
			else
				ang = rotation_quat(axis, angle);
		}

		linalg::vec<T, 3> rotate(linalg::vec<T, 3> vec) const
		{
			return linalg::qrot(ang, vec);
		};

		linalg::vec<T, 3> rotate_vector(linalg::vec<T, 3> vec) const
		{
			return linalg::qrot(ang, vec);
		};

		screw<T,3> rotate_screw(screw<T,3> v) const
		{
			return { rotate_vector(v.ang), rotate_vector(v.lin) };
		};

		linalg::vec<T,3> xdir() const { return linalg::qxdir(ang); }
		linalg::vec<T,3> ydir() const { return linalg::qydir(ang); }
		linalg::vec<T,3> zdir() const { return linalg::qzdir(ang); }

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

		htrans3 inverse()
		{
			auto inv_q = linalg::qinv(ang);

			return
			{
				inv_q,
				-linalg::qrot(inv_q, lin)
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

		/*ssize_t print_to(nos::ostream& out) const
		{
			return nos::fprint_to(out, "htrans({},{})", ang, lin);
		}*/

		htrans3& operator*= (const htrans3& oth) 
		{
			*this = *this * oth;
			return *this;
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