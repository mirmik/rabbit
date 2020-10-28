#ifndef RABBIT_INTERSECT_H
#define RABBIT_INTERSECT_H

#include <rabbit/linalg.h>
#include <rabbit/types.h>
#include <rabbit/prim2.h>

namespace rabbit
{
	template <class T>
	class intersect_node
	{
		bool is_interval;
		T aparam0;
		T aparam1;
		T bparam0;
		T bparam1;
	};

	template <class T>
	int intersect_point_segm2_segm2(
	    const segm2<T>   * segment1,
	    const segm2<T>   * segment2,
	    linalg::vec<T,2> * out_intersection,
	    T epsilon = r_epsilon
	);

	template <class T>
	int __intersect_points_segm2_polysegm2(
	    const segm2<T>     * segm,
	    const polysegm2<T> * poly,
	    linalg::vec<T,2>   * points
	);

	template <class T>
	int intersect_points_segm2_polysegm2(
	    const segm2<T>     * segm,
	    const polysegm2<T> * poly,
	    linalg::vec<T,2>   * points,
	    T epsilon = r_epsilon
	);
}

#endif