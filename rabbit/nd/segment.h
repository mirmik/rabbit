#ifndef RABBIT_NDSEGMENT_H
#define RABBIT_NDSEGMENT_H

#include <ralgo/linalg/vector.h>
#include <ralgo/linalg/vecops.h>

namespace rabbit
{
	namespace nd
	{
		class segment
		{
		public:
			nd::point apnt;
			nd::point bpnt;

			segment(const nd::point& apnt, const nd::point& bpnt) :
				apnt(apnt), bpnt(bpnt)
			{}

			double length() const
			{
				return ralgo::vecops::length(bpnt-apnt);
			}
		};
	}
}

#endif