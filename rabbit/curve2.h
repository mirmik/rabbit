#ifndef RABBIT_CURVE2_H
#define RABBIT_CURVE2_H

#include <linalg.h>
#include <rabbit/trans2.h>

using namespace linalg::aliases;

namespace rabbit 
{
	struct analityc_curve2 
	{
		double tmin;
		double tmax;
		bool periodic;

		virtual double2 d0(double t) = 0;
	};

	struct circle2 
	{
		double radius;
		trans2 trans;

		circle2(double radius_) : radius(radius_), trans() {}
		circle2(double radius_, trans2 trans_) : radius(radius_), trans(trans_) {}

		double2 d0(double t) 
		{			
			return trans( double2 { cos(t) * radius, sin(t) * radius } ); 
		}
	};
}

#endif