#ifndef RABBIT_INTERSECT_H
#define RABBIT_INTERSECT_H

#include <rabbit/linalg.h>
#include <rabbit/types.h>
#include <rabbit/prim2.h>

namespace rabbit
{

	class intersect_node
	{
		bool is_interval;
		r_float aparam0;
		r_float aparam1;
		r_float bparam0;
		r_float bparam1;
	};

	static inline
	rabbit::vec2 intersect_point_line2_line2(
	    const rabbit::line2& alin,
	    const rabbit::line2& blin
	)
	{
		linalg::vec<r_float, 3> a = 
			{ alin.a, alin.b, alin.c };
		linalg::vec<r_float, 3> b = 
			{ blin.a, blin.b, blin.c };

		PRINT(a);
		PRINT(b);
		linalg::vec<r_float, 3> r = linalg::cross(a, b);

		BUG_ON(fabs(r.z) < 1e-5);

		PRINT(r);

		return { r.x/r.z, r.y/r.z };
	}

}

/*static inline
intersect_node intersect_segm2_segm2
(
    const rabbit::segm2& asegm,
    const rabbit::segm2& bsegm)
{
//	line2 alin = asegm.to_line();
//	line2 blin = bsegm.to_line();

//	intersect_node linlin = intersect_line2_line2(alin, blin);
}*/

#endif