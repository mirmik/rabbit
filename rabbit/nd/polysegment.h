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
			bool closed = false;

		public:
			polysegment() = default;
			polysegment(const polysegment&) = default;
			polysegment(polysegment&&) = default;
			polysegment& operator=(const polysegment&) = default;
			polysegment& operator=(polysegment&&) = default;

			void add_point(const nd::point& point)
			{
				data.push_back(point);
			}

			std::vector<nd::point>& points()
			{
				return data;
			}

			size_t npoints() const
			{
				return data.size();
			}

			size_t nsegments() const
			{
				return data.size() - 1;
			}

			std::vector<nd::segment> segments()
			{
				std::vector<nd::segment> ret;
				for (int i = 0; i < nsegments(); i++)
				{
					ret.emplace_back(data[i], data[i + 1]);
				}

				if (closed) 
				{
					ret.emplace_back(data[npoints() - 1], data[0]);
				}

				return ret;
			}
		};
	}
}

#endif