#ifndef RABBIT_SPACE_SCREW_H
#define RABBIT_SPACE_SCREW_H

#include <linalg-v3/linalg.h>

namespace rabbit 
{
	template< class T, int N >
	struct screw;

	template <class T>
	struct screw3 
	{
		linalg::vec<T,3> ang;
		linalg::vec<T,3> lin;

		screw(const linalg::vec<T,3>& ang, const linalg::vec<T,3>& lin);

		screw nlerp(float koeff) 
		{
			return { ang * koeff, lin * koeff };
		} 
	}

	template <class T>
	struct screw2 
	{
		T ang;
		linalg::vec<T,2> lin;

		screw(T ang, const linalg::vec<T,3>& lin);

		screw nlerp(float koeff) 
		{
			return { ang * koeff, lin * koeff };
		} 
	}
}

#endif