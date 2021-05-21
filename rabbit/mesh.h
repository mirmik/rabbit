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
		PRINT(yaw_vertices);
		PRINT(pitch_vertices);

		std::vector<linalg::vec<float, 3>> vertices;
		std::vector<linalg::vec<int, 3>> triangles;

		vertices.resize(2 + yaw_vertices * (pitch_vertices - 1));
		triangles.resize(2 * yaw_vertices * (pitch_vertices) + 50);

		vertices[0] = {0, 0, -radius};

		for (int j = 1; j < pitch_vertices; ++j) // Все, кроме первой и последней.
		{
			for (int i = 0; i < yaw_vertices; ++i)
			{
				float k_yaw = ((float)i / (float)yaw_vertices);
				float k_pitch = ((float)j / (float)pitch_vertices);

				//PRINT(k_pitch);

				float yaw = 2 * M_PI * k_yaw;
				float pitch = -(M_PI / 2) * (1.f - k_pitch) + (M_PI / 2) * k_pitch ;

				nos::println(pitch, k_pitch);
				float x = radius * cos(pitch) * cos(yaw);
				float y = radius * cos(pitch) * sin(yaw);
				float z = radius * sin(pitch);

				nos::println(x, y, z);
				vertices[(1) + ((j - 1)*yaw_vertices) + i] = {x, y, z};

				//nos::println(k_pitch, k_yaw , x, y, z);
			}
		}

		vertices[vertices.size() - 1] = {0, 0, radius};



		for (int i = 0; i < yaw_vertices - 1; ++i)
			triangles[i] = {0, i + 1, i + 2};
		triangles[yaw_vertices] = { 0, yaw_vertices, 1 };

		for (int j = 0; j < pitch_vertices - 2; ++j)
		{
			for (int i = 0; i < yaw_vertices - 1; ++i)
			{
				int a = 1 + i + (    j) * (yaw_vertices);
				int b = 2 + i + (    j) * (yaw_vertices);
				int c = 1 + i + (1 + j) * (yaw_vertices);
				int d = 2 + i + (1 + j) * (yaw_vertices);

				triangles[(yaw_vertices + 2) + (j * (yaw_vertices) + i) * 2 ] = {a, b, c};
				triangles[(yaw_vertices + 2) + (j * (yaw_vertices) + i) * 2 + 1 ] = {d, c, b};
			}

			int a = 1 + (yaw_vertices-1) + (    j) * (yaw_vertices);
			int b = 1 + 0                + (    j) * (yaw_vertices);
			int c = 1 + (yaw_vertices-1) + (1 + j) * (yaw_vertices);
			int d = 1 + 0                + (1 + j) * (yaw_vertices);

			triangles[(yaw_vertices + 2) + (j * (yaw_vertices) + (yaw_vertices - 1)) * 2 ] = {a, b, c};
			triangles[(yaw_vertices + 2) + (j * (yaw_vertices) + (yaw_vertices - 1)) * 2 + 1 ] = {d, c, b};
		}

		int offv = vertices.size() - yaw_vertices - 1;
		int offt = (yaw_vertices + 2) + ((pitch_vertices - 2) * (yaw_vertices) + (yaw_vertices - 1)) * 2 + 1; 
		for (int i = 0; i < yaw_vertices - 1; ++i)
			triangles[offt+i] = {0, offv + i, offv + i + 1};
		triangles[offt+yaw_vertices] = { (int)vertices.size()-1, offv + yaw_vertices, offv + 1 };

		return mesh(std::move(vertices), std::move(triangles));
	}
}

#endif