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
		) : vertices(_vertices), triangles(_triangles)
		{}

		mesh(
		    std::vector<linalg::vec<real, 3>>&& _vertices,
		    std::vector<linalg::vec<int, 3>>&& _triangles
		) : vertices(std::move(_vertices)), triangles(std::move(_triangles))
		{}
	};

	static mesh sphere_rubic_mesh(int yaw_vertices, int pitch_vertices, real radius)
	{
		int iter;

		std::vector<linalg::vec<real, 3>> vertices;
		std::vector<linalg::vec<int, 3>> triangles;

		vertices.resize((yaw_vertices + 1) * (pitch_vertices + 1));
		triangles.resize(2 * yaw_vertices * pitch_vertices);

		iter = 0;
		for (int j = 0; j < pitch_vertices + 1; ++j)
		{
			for (int i = 0; i < yaw_vertices + 1; ++i)
			{
				real k_yaw = ((real)i / (real)yaw_vertices);
				real k_pitch = ((real)j / (real)pitch_vertices);

				real yaw = 2 * M_PI * k_yaw;
				real pitch = -(M_PI / 2) * (1.f - k_pitch) + (M_PI / 2) * k_pitch ;

				real x = radius * cos(pitch) * cos(yaw);
				real y = radius * cos(pitch) * sin(yaw);
				real z = radius * sin(pitch);

				vertices[iter++] = {x, y, z};
			}
		}

		iter = 0;
		for (int j = 0; j < pitch_vertices; ++j)
		{
			for (int i = 0; i < yaw_vertices; ++i)
			{
				int a = i + (    j) * (yaw_vertices + 1);
				int b = i + (    j) * (yaw_vertices + 1) + 1;
				int c = i + (1 + j) * (yaw_vertices + 1);
				int d = i + (1 + j) * (yaw_vertices + 1) + 1;

				triangles[iter++] = {a, b, c};
				triangles[iter++] = {d, c, b};
			}
		}

		return mesh(std::move(vertices), std::move(triangles));
	}

	static mesh surface_rubic_mesh(
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

	static mesh surface_rubic_mesh(
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
}

#endif