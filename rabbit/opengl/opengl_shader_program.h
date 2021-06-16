#ifndef RABBIT_OPENGL_SHADER_H
#define RABBIT_OPENGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <rabbit/types.h>

#if __has_include (<GL/glew.h>)
#include <GL/glew.h>
#else


#if __has_include (<EGL/egl.h>)
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#endif

#endif

namespace rabbit
{
	class opengl_shader_program
	{
	public:
		GLuint Program;

		GLuint id() { return Program; }

		opengl_shader_program();
		opengl_shader_program(const char * vertexPath, const char * fragmentPath);
		void open(const char * vertexPath, const char * fragmentPath);

		void uniform_vec3f(
		    const char * locname, const linalg::vec<float, 3> & v);

		void use();
	};
}

#endif
