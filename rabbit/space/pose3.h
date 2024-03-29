#ifndef RABBIT_SPACE_POSE3_H
#define RABBIT_SPACE_POSE3_H

#include <rabbit/types.h>
#include <rabbit/space/screw.h>

namespace rabbit
{
	template <class T>
	struct pose3
	{
		linalg::vec<T, 4> ang;
		linalg::vec<T, 3> lin;

		pose3();
		pose3(const linalg::vec<T, 4>& q, const linalg::vec<T, 3>& l);
		pose3(const rabbit::screw<T, 3>& scr);

		linalg::vec<T, 3> rotate(linalg::vec<T, 3> vec) const;
		linalg::vec<T, 3> transform(linalg::vec<T, 3> vec) const;
		linalg::vec<T, 3> rotate_vector(linalg::vec<T, 3> vec) const;

		screw<T, 3> rotate_screw(screw<T, 3> v) const;

		linalg::vec<T, 3> xdir() const;
		linalg::vec<T, 3> ydir() const;
		linalg::vec<T, 3> zdir() const;

		pose3 operator * (const pose3& oth);
		pose3& operator *= (const pose3& oth);

		bool operator == (const pose3& oth) const;

		linalg::vec<T, 3> operator()(linalg::vec<T, 3> vec) const;

		pose3 inverse();

		screw<T, 3> to_screw() const;
		linalg::mat<T, 4, 4> to_mat4();

		static
		pose3 from_screw(const screw<T, 3> & scr);

		//ssize_t print_to(nos::ostream& out) const;
	};

	template <class T>
	pose3<T> rot3(linalg::vec<T, 3> vec, T angle);

	template <class T>
	pose3<T> mov3(linalg::vec<T, 3> vec);
}



template <class T>
rabbit::pose3<T> rabbit::rot3(linalg::vec<T, 3> vec, T angle)
{
	return rabbit::pose3<T>(linalg::rotation_quat<T>(vec, angle), {0, 0, 0});
}

template <class T>
rabbit::pose3<T> rabbit::mov3(linalg::vec<T, 3> vec)
{
	return rabbit::pose3<T>({0, 0, 0, 1}, vec);
}

template <class T>
rabbit::pose3<T>::pose3() : ang{0, 0, 0, 1}, lin{0, 0, 0} {}

template <class T>
rabbit::pose3<T>::pose3(
    const linalg::vec<T, 4>& q,
    const linalg::vec<T, 3>& l
)
	: ang(q), lin(l)
{}

template <class T>
rabbit::pose3<T>::pose3(const rabbit::screw<T, 3>& scr)
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

template <class T>
linalg::vec<T, 3> rabbit::pose3<T>::rotate(linalg::vec<T, 3> vec) const
{
	return linalg::qrot(ang, vec);
};

template <class T>
linalg::vec<T, 3> rabbit::pose3<T>::rotate_vector(linalg::vec<T, 3> vec) const
{
	return linalg::qrot(ang, vec);
};

template <class T>
rabbit::screw<T, 3> rabbit::pose3<T>::rotate_screw(screw<T, 3> v) const
{
	return { rotate_vector(v.ang), rotate_vector(v.lin) };
};

template <class T>
linalg::vec<T, 3> rabbit::pose3<T>::xdir() const { return linalg::qxdir(ang); }
template <class T>
linalg::vec<T, 3> rabbit::pose3<T>::ydir() const { return linalg::qydir(ang); }
template <class T>
linalg::vec<T, 3> rabbit::pose3<T>::zdir() const { return linalg::qzdir(ang); }

template <class T>
rabbit::pose3<T> rabbit::pose3<T>::operator * (const rabbit::pose3<T>& oth)
{
	return rabbit::pose3<T>(
	           linalg::qmul(ang, oth.ang),
	           linalg::qrot(ang, oth.lin) + lin
	       );
}

template <class T>
bool rabbit::pose3<T>::operator == (const rabbit::pose3<T>& oth) const
{
	return lin == oth.lin && ang == oth.ang;
}

template <class T>
rabbit::pose3<T> rabbit::pose3<T>::inverse()
{
	auto inv_q = linalg::qinv(ang);

	return
	{
		inv_q,
		-linalg::qrot(inv_q, lin)
	};
}

template <class T>
rabbit::screw<T, 3> rabbit::pose3<T>::to_screw() const
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

template <class T>
rabbit::pose3<T> rabbit::pose3<T>::from_screw(const rabbit::screw<T, 3> & scr) 
{
	auto angle = linalg::length(scr.ang);
	auto axis = scr.ang / angle;

	if (angle == 0) 
	{
		axis = {0, 0, 0};
	}

	return { linalg::rotation_quat(axis, angle), scr.lin };
}

template <class T>
rabbit::pose3<T>& rabbit::pose3<T>::operator*= (const rabbit::pose3<T>& oth)
{
	*this = *this * oth;
	return *this;
}

template <class T>
linalg::mat<T, 4, 4> rabbit::pose3<T>::to_mat4()
{
	return {{qxdir(ang), 0}, {qydir(ang), 0}, {qzdir(ang), 0}, {lin, 1}};
}

template <class T>
linalg::vec<T, 3> rabbit::pose3<T>::transform(linalg::vec<T, 3> arg) const
{
	return linalg::qrot(ang, arg) + lin;
}

template <class T>
linalg::vec<T, 3> rabbit::pose3<T>::operator()(linalg::vec<T, 3> arg) const
{
	return transform(arg);
}






#endif