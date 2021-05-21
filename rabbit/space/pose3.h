#ifndef RABBIT_SPACE_POSE3_H
#define RABBIT_SPACE_POSE3_H

#include <rabbit/types.h>
#include <rabbit/space/screw.h>

namespace rabbit
{
	struct pose3
	{
		vec4 ang;
		vec3 lin;

		pose3();
		pose3(const vec4& q, const vec3& l);
		pose3(const rabbit::screw<real, 3>& scr);

		vec3 rotate(vec3 vec) const;
		vec3 rotate_vector(vec3 vec) const;

		screw<real, 3> rotate_screw(screw<real, 3> v) const;

		vec3 xdir() const;
		vec3 ydir() const;
		vec3 zdir() const;

		pose3 operator * (const pose3& oth);
		pose3& operator *= (const pose3& oth);

		bool operator == (const pose3& oth) const;


		pose3 inverse();

		screw<real, 3> to_screw() const;
		mat4 to_mat4();

		ssize_t print_to(nos::ostream& out) const;
	};

	pose3 rot3(vec3 vec, float angle);
	pose3 mov3(vec3 vec);
}

#endif