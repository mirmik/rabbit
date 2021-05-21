#include <rabbit/space/pose3.h>

using namespace rabbit;

pose3 rabbit::rot3(vec3 vec, real angle)
{
	return pose3(linalg::rotation_quat<real>(vec, angle), {0, 0, 0});
}

pose3 rabbit::mov3(vec3 vec)
{
	return pose3({0, 0, 0, 1}, vec);
}

pose3::pose3() : ang{0, 0, 0, 1}, lin{0, 0, 0} {}

pose3::pose3(
    const vec4& q,
    const vec3& l
)
	: ang(q), lin(l)
{}

pose3::pose3(
    const rabbit::screw<real, 3>& scr
)
	: lin(scr.lin)
{
	auto w = scr.ang;

	auto angle = length(w);
	auto axis = w / angle;

	if (angle == 0)
		ang = {0, 0, 0, 1};
	else
		ang = rotation_quat(axis, angle);
}

vec3 pose3::rotate(vec3 vec) const
{
	return linalg::qrot(ang, vec);
};

vec3 pose3::rotate_vector(vec3 vec) const
{
	return linalg::qrot(ang, vec);
};

screw<real, 3> pose3::rotate_screw(screw<real, 3> v) const
{
	return { rotate_vector(v.ang), rotate_vector(v.lin) };
};

vec3 pose3::xdir() const { return linalg::qxdir(ang); }
vec3 pose3::ydir() const { return linalg::qydir(ang); }
vec3 pose3::zdir() const { return linalg::qzdir(ang); }

pose3 pose3::operator * (const pose3& oth)
{
	return pose3(
	           linalg::qmul(ang, oth.ang),
	           linalg::qrot(ang, oth.lin) + lin
	       );
}

bool pose3::operator == (const pose3& oth) const
{
	return lin == oth.lin && ang == oth.ang;
}

pose3 pose3::inverse()
{
	auto inv_q = linalg::qinv(ang);

	return
	{
		inv_q,
		-linalg::qrot(inv_q, lin)
	};
}

screw<real, 3> pose3::to_screw() const
{
	auto axis = linalg::qaxis(ang);
	auto angle = linalg::qangle(ang);

	if (angle == 0)
	{
		axis = {0, 0, 0};
	}

	return
	{
		axis * angle,
		lin
	};
}

ssize_t pose3::print_to(nos::ostream& out) const
{
	return nos::fprint_to(out, "htrans({},{})", ang, lin);
}

pose3& pose3::operator*= (const pose3& oth)
{
	*this = *this * oth;
	return *this;
}

mat4 pose3::to_mat4()
{
	return {{qxdir(ang), 0}, {qydir(ang), 0}, {qzdir(ang), 0}, {lin, 1}};
}

vec3 pose3::transform(vec3 arg) const 
{
	return linalg::qrot(ang, arg) + lin; 
}

vec3 pose3::operator()(vec3 arg) const 
{
	return transform(arg);
}