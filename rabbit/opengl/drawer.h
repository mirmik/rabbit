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

		void draw_interactive_object(interactive_object & iobj);

		void init_opengl_context();
		void destroy_opengl_context();

		void clean(real r, real g, real b, real a);

		void draw_mesh(
			const rabbit::mesh & mesh, 
			const mat4 & model,
			const mat4 & view,
			const mat4 & projection);
	};
}

#endif