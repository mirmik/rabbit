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
		int iter;

		std::vector<linalg::vec<float, 3>> vertices;
		std::vector<linalg::vec<int, 3>> triangles;

		vertices.resize((yaw_vertices+1) * (pitch_vertices+1));
		triangles.resize(2 * yaw_vertices * pitch_vertices);

		iter = 0;
		for (int j = 0; j < pitch_vertices + 1; ++j)
		{
			for (int i = 0; i < yaw_vertices + 1; ++i)
			{
				nos::println(j, i);
				float k_yaw = ((float)i / (float)yaw_vertices);
				float k_pitch = ((float)j / (float)pitch_vertices);
				nos::println(k_yaw, k_pitch);

				float yaw = 2 * M_PI * k_yaw;
				float pitch = -(M_PI / 2) * (1.f - k_pitch) + (M_PI / 2) * k_pitch ;

				nos::println(yaw, pitch);
				float x = radius * cos(pitch) * cos(yaw);
				float y = radius * cos(pitch) * sin(yaw);
				float z = radius * sin(pitch);

				nos::println(x, y, z);
				vertices[iter++] = {x, y, z};
			}
		}

		iter = 0;
		for (int j = 0; j < pitch_vertices; ++j)
		{
			for (int i = 0; i < yaw_vertices; ++i)
			{
				nos::println(j,i);
				int a = i + (    j) * (yaw_vertices+1);
				int b = i + (    j) * (yaw_vertices+1) + 1;
				int c = i + (1 + j) * (yaw_vertices+1);
				int d = i + (1 + j) * (yaw_vertices+1) + 1;

				triangles[iter++] = {a, b, c};
				triangles[iter++] = {d, c, b};
			}
		}

		return mesh(std::move(vertices), std::move(triangles));
	}
}

#endif