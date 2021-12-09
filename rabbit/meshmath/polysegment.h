#ifndef RABBIT_MESHMATH_POLYSEGMENT_H
#define RABBIT_MESHMATH_POLYSEGMENT_H

#include <igris/container/unbounded_array.h>

namespace rabbit
{
	namespace meshmath
	{
		template <typename T>
		class polysegment
		{
			igris::unbounded_array<T> data;

			polysegment(int dim, int points)
			{
				data.resize(dim*point);
			}

			ralgo::array_view<T> operator[](int i) 
			{
				return { data + dim * i, dim };
			}
		};
	}
}

#endif