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

		public:
			polysegment() = default;
			polysegment(const polysegment&) = default;
			polysegment(polysegment&&) = default;
			polysegment& operator=(const polysegment&) = default;
			polysegment& operator=(polysegment&&) = default;

			polysegment(int dim, int points)
			{
				this->dim = dim;
				data.resize(points);
			}

			void add_point(const nd::point& point) 
			{
				data.push_back(point);
			}

			std::vector<nd::point>& points() 
			{
				return data;
			}
		};
	}
}

#endif