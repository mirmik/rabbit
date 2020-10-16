#ifndef RABBIT_LINALG_H
#define RABBIT_LINALG_H

#include <linalg/linalg.h>
#include <nos/fprint.h>

namespace rabbit
{
	using vec2 =  linalg::vec<r_float, 2>;
	using mat22 = linalg::mat<r_float, 2, 2>;
	using vec3 =  linalg::vec<r_float, 3>;
	using mat33 = linalg::mat<r_float, 3, 3>;

	class trans2
	{
		r_float     ang;
		vec2        lin;

	public:
		trans2(vec2 lin, r_float ang)
			: lin(lin), ang(ang) {}

		trans2 inverse()
		{
			return { linalg::rot(-ang, -lin), -ang };
		}

		trans2 operator * (const trans2& oth)
		{
			return trans2(
			           linalg::rot(ang, oth.lin) + lin,
			           ang + oth.ang);
		}

		trans2 operator() (const trans2& oth) 
		{
			return (*this)(oth);
		}
	};

	r_float vector_angle(vec2 vec) 
	{
		return atan2(vec.y, vec.x);
	}
}

#endif