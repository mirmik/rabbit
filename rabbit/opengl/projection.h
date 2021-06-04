#ifndef RABBIT_OPENGL_PROJECTION_H
#define RABBIT_OPENGL_PROJECTION_H


#include <rabbit/types.h>

namespace rabbit
{

	// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml
	linalg::mat<float, 4, 4> opengl_ortho(
			float left, float right, 
			float bottom, float top, 
			float near, float far)
	{
		real tx = - (right + left) / (right - left);
		real ty = - (top + bottom) / (top - bottom);
		real tz = - (far + near)   / (far - near);

		return
		{
			{2 / (left - right), 0,                  0,                0},
			{0,                  2 / (top - bottom), 0,                0},
			{0,                  0,                  2 / (far - near), 0},
			{tx,                 ty,                 tz,               1}
		};
	}

	// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml
	linalg::mat<float, 4, 4> opengl_perspective(float fovy,
	                                            float aspect,
	                                            float zNear,
	                                            float zFar)
	{
		real angle = fovy / 2;
		real f = cos(angle) / sin(angle);

		return
		{
			{f / aspect, 0, 0,                                0},
			{0,          f, 0,                                0},
			{0,          0, (zFar + zNear) / (zNear - zFar), -1},
			{0,          0, 2 * zFar*zNear / (zNear - zFar),  0}
		};
	}
}

#endif