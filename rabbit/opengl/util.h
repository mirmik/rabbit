#ifndef RABBIT_OPENGL_UTIL_H
#define RABBIT_OPENGL_UTIL_H

#define GLCHECK(...) \
	{ \
		__VA_ARGS__; \
		GLenum err = glGetError(); \
		if (err != GL_NO_ERROR) \
		{ \
			nos::fprint("%s:%d:%s\n", __FILE__, __LINE__, gluErrorString(err)); \
			assert(0); \
		} \
	}

#endif