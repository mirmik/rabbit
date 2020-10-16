#ifndef RABBIT_GPARAMS_H
#define RABBIT_GPARAMS_H

#include <rabbit/types.h>
#include <rabbit/linalg.h>

namespace rabbit
{
	namespace gparam
	{
		class circ
		{
			trans2  pose;
			r_float radius;

		public:
			circ(trans2 axes, r_float radius) :
				pose(axes), radius(radius)
			{}

			circ transformed_by(trans2 trsf)
			{
				return { trsf * pose, radius };
			}
		};

		class lin
		{
			trans2  pose;

			lin(const trans2& trsf)
				: pose(trsf)
			{}

			lin(vec2 apnt, vec2 bpnt)
				: pose(apnt, vector_angle(bpnt - apnt))
			{}

			lin transformed_by(trans2 trsf)
			{
				return { trsf * pose };
			}
		};
	}
}

#endif