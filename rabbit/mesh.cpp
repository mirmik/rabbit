#include <rabbit/mesh.h>

#include <rabbit/third/stl_reader.h>

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



mesh rabbit::mesh_from_file(const char * path)
{
	std::vector<float> coords, normals;
	std::vector<unsigned int> tris, solids;

	std::vector<linalg::vec<real, 3>> vertices;
	std::vector<linalg::vec<int, 3>> triangles;
	
	stl_reader::ReadStlFile ("bulbasaur_dual_body.STL", coords, normals, tris, solids);
	
	int vertices_total = coords.size() / 3;
	int triangles_total = tris.size() / 3;

	vertices.resize(vertices_total);
	triangles.resize(triangles_total);

	for (int i = 0; i < vertices_total; ++i) 
		vertices[i] = { coords[i*3], coords[i*3+1], coords[i*3+2] };  

	for (int i = 0; i < triangles_total; ++i) 
		triangles[i] = { tris[i*3], tris[i*3+1], tris[i*3+2] };  

	return mesh(std::move(vertices), std::move(triangles));
}


vec3 rabbit::mesh::center() 
{
	linalg::vec<double, 3> acc = { 0, 0, 0 };
	int n = 0

	for (auto & v : vertices) 
	{
		acc += v;
	}

	return acc / n;
}