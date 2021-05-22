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

		GLuint VBO=0, VAO=0, EBO=0;
		int vertices_stride = 3;

		void set_buffers(int vao, int vbo, int ebo) { VAO = vao; VBO = vbo; EBO = ebo; }
		void set_vertices_stride(int arg) { vertices_stride = arg; }

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

		void draw_triangles(
		    float * vertices,
		    int vertices_total,
		    GLuint * triangles,
		    int triangles_total);

		void draw_triangles(
		    const std::vector<vec3> & vertices,
		    const std::vector<ivec3> & triangles);


		void uniform_mat4f(
			unsigned int loc, const linalg::mat<float, 4, 4> & matrix);
		
		void uniform_mat4f(
			const char * locname, int program, const linalg::mat<float, 4, 4> & matrix);

		void uniform_mat4f(
			unsigned int loc, const GLfloat* matrix);
		
		void uniform_mat4f(
			const char * locname, int program, const GLfloat* matrix);

	};
}
#endif