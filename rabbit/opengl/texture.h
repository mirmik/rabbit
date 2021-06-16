#ifndef RABBIT_OPENGL_TEXTURE_H
#define RABBIT_OPENGL_TEXTURE_H

#include <GL/gl.h>

namespace rabbit
{
	class opengl_texture
	{
		unsigned char * data = nullptr;
		int width;
		int height;

		GLuint texture;

		GLint opengl_format;
		GLint format;
		GLint type;

	public:
		void resize(int w, int h) 
		{
			if (data) delete[] (data);

			data = new unsigned char[w*h];
			width = w;
			height = h;
		}

		void set_test_texture() 
		{
			for (int i = 0; i < width; ++i) 
				for (int j = 0; j < height; ++j) 
					data[i * width + j] = (i+j) % 2 ? 255 : 0;
		}

		void bind()
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
			    GL_TEXTURE_2D,
			    0,
			    GL_RED,
			    width,
			    height,
			    0,
			    GL_RED,
			    GL_UNSIGNED_BYTE,
			    data
			);

		}

		void activate(int program_id, const char * name, int no = 0) const
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(glGetUniformLocation(program_id, name), no);
		}
	};
}

#endif