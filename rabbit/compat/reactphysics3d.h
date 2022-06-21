#ifndef RABBIT_REACT_CAST
#define RABBIT_REACT_CAST

#include <ralgo/linalg/linalg.h>
#include <ralgo/linalg/extlinalg.h>
#include <ralgo/space/pose3.h>
#include <reactphysics3d/reactphysics3d.h>

namespace rabbit 
{
	static_assert(sizeof(reactphysics3d::decimal) == sizeof(float));

	static inline linalg::vec<float,3> react_cast(const reactphysics3d::Vector3& v) 
	{
		return { v.x, v.y, v.z };
	}

	static inline linalg::vec<float,4> react_cast(const reactphysics3d::Quaternion& q) 
	{
		return { q.x, q.y, q.z, q.w };
	}

	static inline ralgo::pose3<float> react_cast(const reactphysics3d::Transform& t) 
	{
		return { react_cast(t.getOrientation()), react_cast(t.getPosition()) };
	}

	static inline reactphysics3d::Vector3 react_cast(const linalg::vec<float,3>& v) 
	{
		return { v.x, v.y, v.z };
	}

	static inline reactphysics3d::Quaternion react_cast(const linalg::vec<float,4>& q) 
	{
		return { q.x, q.y, q.z, q.w };
	}

	static inline reactphysics3d::Transform react_cast(const ralgo::pose3<float>& t) 
	{
		return { react_cast(t.lin), react_cast(t.ang) };
	}

	/*static inline linalg::mat<float,4,4> react_world_frame_inertia_tensor(const reactphysics3d::RigidBody& rb) 
	{
		auto mass = rb.getMass();
		auto inertia = react_cast(rb.getLocalInertiaTensor());
		auto center = react_cast(rb.getLocalCenterOfMass());
		auto trans = react_cast(rb.getTransform());

		auto wf_inertia = trans.rotate_quadric_form(ralgo::diag(inertia));
		auto wf_center = trans.rotate_vector(center);
		auto wf_center_tensor = ralgo::antisymmetric_tensor(wf_center);

		/// 
	}*/

	// Теорема Штайнера
	static inline linalg::mat<float,3,3> react_world_inertia_for_center(
		const reactphysics3d::RigidBody& rb,
		const linalg::vec<float, 3>& target
	) 
	{
		return steiner(
        	rb.getMass(),
        	react_cast(rb.getLocalInertiaTensor()), 
        	react_cast(rb.getLocalCenterOfMass()),
        	react_cast(rb.getTransform()),
        	target
	    );
	}
} 

#endif