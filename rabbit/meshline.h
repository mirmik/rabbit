#ifndef RABBIT_MESHLINE_H
#define RABBIT_MESHLINE_H

#include <rabbit/types.h>
#include <rabbit/geom/curve.h>

namespace rabbit 
{
	class meshline 
	{
		std::vector<vec3> vertices;
		std::vector<ivec2> lines;
	};

	meshline rubic_curve_meshline(const curve & crv);
} 

#endif