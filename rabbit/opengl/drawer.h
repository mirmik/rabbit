#ifndef RABBIT_OPENGL_DRAWER_H
#define RABBIT_OPENGL_DRAWER_H

#include <rabbit/types.h>
#include <rabbit/opengl/opengl_shader_program.h>
#include <rabbit/interactive/interactive_object.h>

namespace rabbit
{
	class opengl_drawer
	{
	public:
		opengl_drawer();

		GLuint VBO, VAO, EBO;
		opengl_shader_program opengl_mesh_program;
		opengl_shader_program opengl_simple_program;

		void draw_interactive_object(interactive_object & iobj);

		void init_opengl_context();
		void destroy_opengl_context();

		void clean(real r, real g, real b, real a);

		void draw_mesh(
		    const rabbit::mesh & mesh,
		    const mat4 & model,
		    const mat4 & view,
		    const mat4 & projection);

		void draw_points(
		    const vec3 * pnts,
		    int count,
		    const mat4 & model,
		    const mat4 & view,
		    const mat4 & projection);


		void draw_points(
		    const std::vector<vec3> & pnts,
		    const mat4 & model,
		    const mat4 & view,
		    const mat4 & projection)
		{
			draw_points(pnts.data(), pnts.size(), model, view, projection);
		}




		void create_buffers();

		void draw_simple_triangles(
		    float * vertices,
		    int vertices_total,
		    GLuint * triangles,
		    int triangles_total);

		void draw_simple_triangles(
		    const std::vector<vec3> & vertices,
		    const std::vector<ivec3> & triangles);

	};
}
#endif