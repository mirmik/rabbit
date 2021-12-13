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
			std::vector<nd::point> data;
			int dim;
			int points;

		public:
			polysegment() = default;
			polysegment(const polysegment&) = default;
			polysegment(polysegment&&) = default;
			polysegment& operator=(const polysegment&) = default;
			polysegment& operator=(polysegment&&) = default;

			polysegment(int dim, int points)
			{
				this->dim = dim;
				this->points = points; 
				data.resize(points);
			}

			nd::point& operator[](int i) 
			{
				return data[i];
			}

			void add_last_point(const nd::point& point) 
			{
				data.push_back(point);
			}
		};
	}
}

#endif