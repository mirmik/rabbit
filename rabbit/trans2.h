#ifndef RABBIT_TRANS2_H
#define RABBIT_TRANS2_H

#include <linalg.h>
#include <linalg-ext.h>

using namespace linalg::aliases;

namespace rabbit 
{
	struct trans2 
	{
		double2 translate;
		double rotate;

		trans2() : translate{0,0}, rotate(0) {}
		trans2(double2 translate_, double rotate_) : translate(translate_), rotate(rotate_) {}

		double2 operator()(double2 vec) { return linalg::rot(rotate, vec) + translate; };
	};
}

#endif