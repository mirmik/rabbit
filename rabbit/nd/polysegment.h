#ifndef RABBIT_MESHMATH_POLYSEGMENT_H
#define RABBIT_MESHMATH_POLYSEGMENT_H

#include <vector>
#include <rabbit/nd/point.h>

namespace rabbit
{
	namespace nd
	{
		class polysegment
		{
			std::vector<double> data;
			int dim;
			int points;

		public:
			polysegment(int dim, int points)
			{
				this->dim = dim;
				this->points = points; 
				data.resize(dim*points);
			}

			nd::point operator[](int i) 
			{
				return nd::point(data.data() + dim * i, dim);
			}
		};
	}
}

#endif