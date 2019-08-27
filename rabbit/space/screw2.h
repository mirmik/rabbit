#ifndef RABBIT_SPACE2_H
#define RABBIT_SPACE2_H

#include <rabbit/linalg.h>

namespace rabbit 
{
	template <class T>
	struct screw2<T>
	{
		T ang;
		linalg::vec<T,2> lin;

		screw(T ang, const linalg::vec<T,3>& lin);

		screw nlerp(float koeff) 
		{
			return { ang * koeff, lin * koeff };
		} 
	};
}


#endif