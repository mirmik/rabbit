#ifndef RABBIT_MESH_H
#define RABBIT_MESH_H

#include <rabbit/third/linalg.h>
#include <rabbit/geom/surface.h>
#include <vector>

namespace rabbit
{
	class mesh
	{
	public:
		std::vector<linalg::vec<float, 3>> vertices;
		std::vector<linalg::vec<unsigned int, 3>> triangles;

		mesh(
		    const std::vector<linalg::vec<float, 3>>& _vertices,
		    const std::vector<linalg::vec<unsigned int, 3>>& _triangles
		);

		mesh(
		    std::vector<linalg::vec<float, 3>>&& _vertices,
		    std::vector<linalg::vec<unsigned int, 3>>&& _triangles
		);

		vec3f center();
		void correct_center();
	};

	mesh surface_rubic_mesh(
	    surface & surf,
	    float ustrt, float ufini, int utotal,
	    float vstrt, float vfini, int vtotal);

	mesh surface_rubic_mesh(
	    surface & surf,
	    int utotal,
	    int vtotal);


	mesh mesh_from_file(const char * path);
}

#endif