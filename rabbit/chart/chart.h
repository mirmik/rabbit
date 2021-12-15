/** @file Графики на движке opengl */

#ifndef RABBIT_CHARTS_H
#define RABBIT_CHARTS_H

#include <rabbit/opengl/drawer.h>
#include <ralgo/signal/sliding_array.h>

namespace rabbit
{
	struct xypoint
	{
		float x;
		float y;
		xypoint(float x, float y) : x(x), y(y) {}
	};

	/*class xyseries
	{
		std::vector<xypoint> data;

		void push_back(xypoint point)
		{
			data.push_back(point);
		}
	}*/

	class chart_axis 
	{
		
	};

	class xyseries_basic
	{
	public:
		virtual void buffer(xypoint ** arr, int * siz) = 0; 
		virtual void minmax(linalg::vec<float,2> & min, linalg::vec<float,2> & max) = 0; 
	};

	class xyseries : public xyseries_basic
	{
		std::vector<xyseries> points;

		void append(const xypoint & pnt) {}
	};

	class sliding_xyseries : public xyseries_basic
	{	
		ralgo::sliding_array<xypoint> array;

		void buffer(xypoint ** arr, int * siz) 
		{
			auto view = array.window();
			*arr = (xypoint*)view.data();
			*siz = view.size();
		}
	};

	class chart 
	{
		std::vector<xyseries *> series;

	public:
		chart()
		{

		}

		void add_series(xyseries * xys) 
		{
			series.push_back(xys);
		}
	};



	class opengl_viewport
	{
		int l, r, b, t;

	public:
		void set_chart_viewport(int width, int height)
		{
			l = 200;
			t = 20;
			r = width - l;
			b = height - 50 - t;
		}

		void apply_viewport() const
		{
			glViewport(l, t, r, b);
		}
	};

		const char * chart_vertex_shader  = R"""(
#version 300 es
layout (location = 0) in vec2 position;

void main()
{
    gl_Position = vec4(position, 0.0f, 1.0f);
}
)""";

		const char * chart_fragment_shader = R"""(
#version 300 es

uniform lowp vec3 Color;
out lowp vec4 color;

void main()
{
    color = vec4(Color, 1.0f);
} 
)""";		

	class opengl_chart_drawer : public opengl_drawer
	{
	public:
		opengl_chart_drawer()
		{
			chart_program.open(
			    chart_vertex_shader,
			    chart_fragment_shader
			);
		}

		opengl_shader_program chart_program;

		void draw_xyseries(
			xypoint * points, 
			int count, 
			const linalg::vec<float,3> & color, 
			const opengl_viewport & viewport)
		{
			viewport.apply_viewport();

			set_vertices_stride(2);

			chart_program.use();
			chart_program.uniform_vec3f("Color", color);
			draw_lines((float*)points, count, GL_LINE_STRIP);
			glUseProgram(0);
		}
	};
}

#endif