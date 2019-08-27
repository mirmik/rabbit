#ifndef RABBIT_SPACE_SCREW_H
#define RABBIT_SPACE_SCREW_H

#include <linalg-v3/linalg.h>

namespace rabbit 
{
	template< class T, int N >
	struct screw;

	template <class T>
	using screw2 = screw<T,2>;

	template <class T>
	using screw3 = screw<T,3>;

	template <class T>
	struct screw<T,3> 
	{
		linalg::vec<T,3> ang;
		linalg::vec<T,3> lin;

		screw(const linalg::vec<T,3>& ang, const linalg::vec<T,3>& lin);

		screw operator * (float koeff) 
		{
			return { ang * koeff, lin * koeff };
		}

		T rotation() { return ang; }
		linalg::vec<T,3> translation() { return lin; }
	};

	template <class T>
	struct screw<T,2>
	{
		T ang;
		linalg::vec<T,2> lin;

		screw(T ang, const linalg::vec<T,2>& lin) : ang(ang), lin(lin) {}
		screw(){}

		screw operator * (float koeff) 
		{
			return { ang * koeff, lin * koeff };
		}

		T rotation() { return ang; }
		linalg::vec<T,2> translation() { return lin; }
	};
}

#endif