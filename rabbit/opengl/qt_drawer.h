#ifndef RABBIT_QT_OPENGL_DRAWER_H
#define RABBIT_QT_OPENGL_DRAWER_H

#include <QGLFunctions>
#include <rabbit/opengl/abstract_drawer.h>
//#include <rabbit/opengl/opengl_shader_program.h>

namespace rabbit 
{
	class qt_opengl_drawer : public rabbit::opengl_abstract_drawer
	{
		QGLFunctions gl;
		//void init_opengl_context();
	};
}

#endif