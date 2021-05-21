#ifndef RABBIT_OPENGL_SHADER_H
#define RABBIT_OPENGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include <rabbit/types.h>

namespace rabbit
{
	class opengl_shader_program
	{
	public:
		GLuint Program;

		opengl_shader_program();
		opengl_shader_program(const char * vertexPath, const char * fragmentPath);
		void open(const char * vertexPath, const char * fragmentPath);

		void use();

		void uniform_mat4f(
			const char * locname, const linalg::mat<float, 4, 4> & matrix);
	};
}

#endif
