#ifndef RABBIT_TYPES_H
#define RABBIT_TYPES_H

#include <rabbit/linalg.h>

#ifndef RABBIT_REAL_TYPE
#define RABBIT_REAL_TYPE float
#endif

typedef float r_float;
const r_float r_epsilon = 1e-5;

namespace rabbit 
{
	using real = RABBIT_REAL_TYPE;
	const real epsilon = 1e-10; 

	using vec2 = linalg::vec<real, 2>;
	using vec3 = linalg::vec<real, 3>;
	using vec4 = linalg::vec<real, 4>;

	using mat22 = linalg::mat<real, 2, 2>;
	using mat23 = linalg::mat<real, 2, 3>;
	using mat24 = linalg::mat<real, 2, 4>;

	using mat32 = linalg::mat<real, 3, 2>;
	using mat33 = linalg::mat<real, 3, 3>;
	using mat34 = linalg::mat<real, 3, 4>;

	using mat42 = linalg::mat<real, 4, 2>;
	using mat43 = linalg::mat<real, 4, 3>;
	using mat44 = linalg::mat<real, 4, 4>;

	using mat2 = linalg::mat<real, 2, 2>;
	using mat3 = linalg::mat<real, 3, 3>;
	using mat4 = linalg::mat<real, 4, 4>;
} 

#endif