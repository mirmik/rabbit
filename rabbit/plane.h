#ifndef RABBIT_PLANE_H
#define RABBIT_PLANE_H

#include <linalg.h>
#include <rabbit/pntvec.h>

namespace rabbit 
{
	template <class T>
	struct plane 
	{
		linalg::vec<T,3> n; ///< normal - unit vector
		T l;				///< distance between plane and original point

		constexpr plane(linalg::vec<T,3> pnt, linalg::vec<T,3> norm) : n(norm), l(dot(pnt, norm)) {}

		size_t print_to(nos::ostream & o) const 
		{
			return nos::fprint_to(o, "plane(n:{},l:{})", n, l);
		}
	};
}

#endif