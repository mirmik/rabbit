#ifndef RABBIT_MESH_H
#define RABBIT_MESH_H

#include <linalg/linalg.h>

namespace rabbit
{
	class mesh
	{
	public:
		std::vector<linalg::vec<float, 3>> vertices;
		std::vector<linalg::vec<int, 3>> triangles;

		mesh(
		    const std::vector<linalg::vec<float, 3>>& _vertices,
		    const std::vector<linalg::vec<int, 3>>& _triangles
		) : vertices(_vertices), triangles(_triangles)
		{}

		mesh(
		    std::vector<linalg::vec<float, 3>>&& _vertices,
		    std::vector<linalg::vec<int, 3>>&& _triangles
		) : vertices(std::move(_vertices)), triangles(std::move(_triangles))
		{}
	};

	mesh sphere_rubic_mesh(int yaw_vertices, int pitch_vertices, float radius)
	{
		std::vector<linalg::vec<float, 3>> vertices;
		std::vector<linalg::vec<int, 3>> triangles;

		vertices.resize(2 + yaw_vertices * (pitch_vertices-1));
		triangles.resize(2 * yaw_vertices * (pitch_vertices + 1));

		vertices[0] = {0, 0, -radius};

		for (int j = 1; j < pitch_vertices; ++j) // Все, кроме первой и последней.
		{
			for (int i = 0; i < yaw_vertices; ++i)
			{
				float k_yaw = ((float)i / (float)yaw_vertices);
				float k_pitch = ((float)j / (float)pitch_vertices);

				float yaw = 2*M_PI * k_yaw;
				float pitch = -M_PI * (1.f - k_pitch) + M_PI * k_pitch ;

				float x = radius * sin(pitch) * cos(yaw);
				float y = radius * sin(pitch) * sin(yaw);
				float z = radius * cos(pitch);
				vertices[1 + i + (j-1) * yaw_vertices] = {x, y, z};

				//nos::println(k_pitch, k_yaw , x, y, z);
			}
		}

		vertices[vertices.size() - 1] = {0, 0, radius};



		for (int i = 1; i < yaw_vertices; ++i)
			triangles[i] = {0, i, i + 1};
		triangles[yaw_vertices] = { 0, yaw_vertices, 1 };

		for (int j = 0; j < pitch_vertices - 1; ++j)
		{
			for (int i = 0; i < yaw_vertices - 1; ++i)
			{
				int a = 1 + i + (    j) * yaw_vertices;
				int b = 2 + i + (    j) * yaw_vertices;
				int c = 1 + i + (1 + j) * yaw_vertices;
				int d = 2 + i + (1 + j) * yaw_vertices;

				triangles[2*(j*yaw_vertices + i)  ] = {a, b, c};
				triangles[2*(j*yaw_vertices + i)+1] = {d, c, b};
			}
		}

		//for (int i = 0; i < yaw_vertices - 1; ++i)
		//	triangles.emplace_back(0, i, i + 1);
		//triangles.emplace_back(0, yaw_vertices, 1);

		return mesh(std::move(vertices), std::move(triangles));
	}
}

#endif