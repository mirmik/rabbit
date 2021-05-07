#ifndef RABBIT_TYPES_H
#define RABBIT_TYPES_H

#ifndef RABBIT_REAL_TYPE
#define RABBIT_REAL_TYPE float
#endif

typedef float r_float;
const r_float r_epsilon = 1e-5;

namespace rabbit 
{
	using real = RABBIT_REAL_TYPE;
	const real epsilon = 1e-5; 
} 

#endif