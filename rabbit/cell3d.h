#ifndef RABBIT_CELL3D_H
#define RABBIT_CELL3D_H

namespace rabbit 
{
	
	struct cell3d
	{
		linalg::vec<float, 3> ll;
		linalg::vec<float, 3> hl;
		linalg::vec<float, 3> lh;
		linalg::vec<float, 3> hh;
	};
}

#endif