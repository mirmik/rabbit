#ifndef RABBIT_SPACE_POSE2_H
#define RABBIT_SPACE_POSE2_H

#include <rabbit/types.h>

namespace rabbit
{
	class pose2
	{
		vec2        lin;
		r_float     ang;
		
	public:
		pose2(vec2 lin, r_float ang)
			: lin(lin), ang(ang) {}

		pose2 inverse()
		{
			return { linalg::rot(-ang, -lin), -ang };
		}

		pose2 operator * (const pose2& oth)
		{
			return pose2(
			           linalg::rot(ang, oth.lin) + lin,
			           ang + oth.ang);
		}

		/*pose2 operator() (const pose2& oth) 
		{
			return (*this)(oth);
		}*/

		vec2 transform_vector(const vec2& vec) const
		{
			return linalg::rot(ang, vec);
		}

		vec2 transform_point(const vec2& vec) const
		{
			return linalg::rot(ang, vec) + lin;
		}
	};

	static inline
	r_float vector_angle(vec2 vec) 
	{
		return atan2(vec.y, vec.x);
	}
}

#endif