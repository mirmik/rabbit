#ifndef RABBIT_MESH_H
#define RABBIT_MESH_H

#include <linalg/linalg.h>
#include <rabbit/geom/surface.h>

namespace rabbit
{
	class mesh
	{
	public:
		std::vector<linalg::vec<real, 3>> vertices;
		std::vector<linalg::vec<int, 3>> triangles;

		mesh(
		    const std::vector<linalg::vec<real, 3>>& _vertices,
		    const std::vector<linalg::vec<int, 3>>& _triangles
		);

		mesh(
		    std::vector<linalg::vec<real, 3>>&& _vertices,
		    std::vector<linalg::vec<int, 3>>&& _triangles
		);
	};

	mesh surface_rubic_mesh(
	    surface & surf,
	    real ustrt, real ufini, int utotal,
	    real vstrt, real vfini, int vtotal);

	mesh surface_rubic_mesh(
	    surface & surf,
	    int utotal,
	    int vtotal);


	mesh mesh_from_file(const char * path);
}

#endif