#ifndef RABBIT_TYPES_H
#define RABBIT_TYPES_H

#include <rabbit/third/linalg.h>

#ifndef RABBIT_REAL_TYPE
#define RABBIT_REAL_TYPE double
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

	using vec2f = linalg::vec<float, 2>;
	using vec3f = linalg::vec<float, 3>;
	using vec4f = linalg::vec<float, 4>;

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

	using mat22f = linalg::mat<float, 2, 2>;
	using mat23f = linalg::mat<float, 2, 3>;
	using mat24f = linalg::mat<float, 2, 4>;

	using mat32f = linalg::mat<float, 3, 2>;
	using mat33f = linalg::mat<float, 3, 3>;
	using mat34f = linalg::mat<float, 3, 4>;

	using mat42f = linalg::mat<float, 4, 2>;
	using mat43f = linalg::mat<float, 4, 3>;
	using mat44f = linalg::mat<float, 4, 4>;

	using mat2f = linalg::mat<float, 2, 2>;
	using mat3f = linalg::mat<float, 3, 3>;
	using mat4f = linalg::mat<float, 4, 4>;

	using ivec2 = linalg::vec<int32_t, 2>;
	using ivec3 = linalg::vec<int32_t, 3>;
	using ivec4 = linalg::vec<int32_t, 4>;

	using imat22 = linalg::mat<int32_t, 2, 2>;
	using imat23 = linalg::mat<int32_t, 2, 3>;
	using imat24 = linalg::mat<int32_t, 2, 4>;

	using imat32 = linalg::mat<int32_t, 3, 2>;
	using imat33 = linalg::mat<int32_t, 3, 3>;
	using imat34 = linalg::mat<int32_t, 3, 4>;

	using imat42 = linalg::mat<int32_t, 4, 2>;
	using imat43 = linalg::mat<int32_t, 4, 3>;
	using imat44 = linalg::mat<int32_t, 4, 4>;

	using imat2 = linalg::mat<int32_t, 2, 2>;
	using imat3 = linalg::mat<int32_t, 3, 3>;
	using imat4 = linalg::mat<int32_t, 4, 4>;

} 

#endif