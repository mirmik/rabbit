#ifndef RABBIT_UTIL_H
#define RABBIT_UTIL_H

#include <rabbit/linalg.h>
#include <rabbit/types.h>

namespace rabbit 
{
	template <class T, int N, class IT, class EIT>
	IT
	nearest_point_from_array(
		const linalg::vec<T,N>& pnt,
		IT  it,
		EIT eit
	) 
	{
		T dist;
		IT minit = it;
		T mindist = linalg::distance(pnt, *it++);

		for (; it!=eit; ++it) 
		{
			dist = linalg::distance(pnt, *it);

			if (mindist > dist) 
			{
				mindist = dist;
				minit = it;
			} 
		}

		return minit;
	}

	static real deg(real x) { return x * (real)M_PI / (real)180.; }
}

#endif