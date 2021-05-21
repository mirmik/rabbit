#include <rabbit/mesh.h>

using namespace rabbit;

rabbit::mesh::mesh(
    const std::vector<linalg::vec<real, 3>>& _vertices,
    const std::vector<linalg::vec<int, 3>>& _triangles
) : vertices(_vertices), triangles(_triangles)
{}

rabbit::mesh::mesh(
    std::vector<linalg::vec<real, 3>>&& _vertices,
    std::vector<linalg::vec<int, 3>>&& _triangles
) : vertices(std::move(_vertices)), triangles(std::move(_triangles))
{}

mesh rabbit::surface_rubic_mesh(
    surface & surf,
    real ustrt, real ufini, int utotal,
    real vstrt, real vfini, int vtotal)
{
	int iter;

	std::vector<linalg::vec<real, 3>> vertices;
	std::vector<linalg::vec<int, 3>> triangles;

	vertices.resize((utotal + 1) * (vtotal + 1));
	triangles.resize(2 * utotal * vtotal);

	iter = 0;
	for (int j = 0; j < vtotal + 1; ++j)
	{
		for (int i = 0; i < utotal + 1; ++i)
		{
			real ku = ((real)i / (real)utotal);
			real kv = ((real)j / (real)vtotal);

			real u = ustrt * ((real)1. - ku) + ufini * ku;
			real v = vstrt * ((real)1. - kv) + vfini * kv;

			vertices[iter++] = surf.value(u, v);
		}
	}

	iter = 0;
	for (int j = 0; j < vtotal; ++j)
	{
		for (int i = 0; i < utotal; ++i)
		{
			int a = i + (    j) * (utotal + 1);
			int b = i + (    j) * (utotal + 1) + 1;
			int c = i + (1 + j) * (utotal + 1);
			int d = i + (1 + j) * (utotal + 1) + 1;

			triangles[iter++] = {a, b, c};
			triangles[iter++] = {d, c, b};
		}
	}

	return mesh(std::move(vertices), std::move(triangles));
}

mesh rabbit::surface_rubic_mesh(
    surface & surf,
    int utotal,
    int vtotal)
{
	return surface_rubic_mesh(
	           surf,
	           surf.umin(), surf.umax(), utotal,
	           surf.vmin(), surf.vmax(), vtotal
	       );
}