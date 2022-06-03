#ifndef RABBiT_OPENGL_ABSTRACT_DRAWER_H_
#define RABBiT_OPENGL_ABSTRACT_DRAWER_H_

#include <igris/container/array_view.h>
#include <vector>

namespace rabbit 
{
	class opengl_abstract_drawer 
	{
	public:
		virtual void draw_mesh(
		    const rabbit::mesh<float> & mesh,
		    const mat4f & model,
		    const mat4f & view,
		    const mat4f & projection) = 0;

		virtual void draw_points(
		    const vec3f * pnts,
		    int count,
		    const mat4f & model,
		    const mat4f & view,
		    const mat4f & projection) = 0;

		void draw_points(
		    const std::vector<vec3f> & pnts,
		    const mat4f & model,
		    const mat4f & view,
		    const mat4f & projection)
		{
			draw_points(pnts.data(), pnts.size(), model, view, projection);
		}

		virtual void draw_lines(
		    const std::vector<vec3f> & lines) = 0;


		virtual void draw_points2d(
		    const igris::array_view<vec2f> & points,
		    GLint style) = 0;

		virtual void draw_points3d(
		    const igris::array_view<vec3f> & points,
		    GLint style) = 0;

		virtual void draw_points3d(
		    const igris::array_view<vec3f> & lines, 
			GLint style,
		    const rabbit::mat4f& model,
		    const rabbit::mat4f& view,
		    const rabbit::mat4f& projective
		) = 0;

		void draw_lines2d(
		    const igris::array_view<vec2f> & lines) 
		{
			return draw_points2d(lines, GL_LINE_STRIP);
		}

		void draw_lines2d(
		    const std::vector<vec2f>& lines) 
		{
			return draw_lines2d(
				igris::array_view<vec2f>(
					(vec2f*)lines.data(), lines.size()));	
		}

		void draw_lines3d(
		    const igris::array_view<vec3f> & lines) 
		{
			return draw_points3d(lines, GL_LINE_STRIP);
		}

		void draw_lines3d(
		    const std::vector<vec3f>& lines) 
		{
			return draw_lines3d(
				igris::array_view<vec3f>(
					(vec3f*)lines.data(), lines.size()));	
		}

		void draw_line2d(
		    const vec2f& a, const vec2f& b) 
		{
			return draw_points2d({a,b}, GL_LINE_STRIP);
		}

		void draw_line3d(
		    const vec3f& a, const vec3f& b) 
		{
			return draw_points3d({a,b}, GL_LINE_STRIP);
		}
	};
}

#endif