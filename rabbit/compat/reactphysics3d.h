#ifndef RABBIT_REACT_CAST
#define RABBIT_REACT_CAST

#include <ralgo/linalg/linalg.h>
#include <reactphysics3d/reactphysics3d.h>

namespace rabbit 
{
	static_assert(sizeof(reactphysics3d::decimal) == sizeof(float));

	const linalg::vec<float,3> react_cast(const reactphysics3d::Vector3& v) 
	{
		return { v.x, v.y, v.z };
	}

	const linalg::vec<float,4> react_cast(const reactphysics3d::Quaternion& q) 
	{
		return { q.x, q.y, q.z, q.w };
	}

	const ralgo::pose3<float> react_cast(const reactphysics3d::Transform& t) 
	{
		return { react_cast(t.getOrientation()), react_cast(t.getPosition()) };
	}

	const reactphysics3d::Vector3 react_cast(const linalg::vec<float,3>& v) 
	{
		return { v.x, v.y, v.z };
	}

	const reactphysics3d::Quaternion react_cast(const linalg::vec<float,4>& q) 
	{
		return { q.x, q.y, q.z, q.w };
	}

	const reactphysics3d::Transform react_cast(const ralgo::pose3<float>& t) 
	{
		return { react_cast(t.lin), react_cast(t.ang) };
	}
} 

#endif