#ifndef RABBIT_OPENGL_QTSCENE_H
#define RABBIT_OPENGL_QTSCENE_H

#include <rabbit/opengl/drawer.h> 
#include <rabbit/camera.h> 
#include <rabbit/opengl/projection.h>
#include <rabbit/util.h>

namespace rabbit 
{
	class scene;
	class view;

	class drawable_object 
	{
	public:
		ralgo::pose3<float> pose;

	public:
		drawable_object() : pose({0,0,0,1},{0,0,0}) {}
		virtual void draw_on(rabbit::view& view) = 0;
	};

	class view
	{
	public:
		rabbit::opengl_drawer drawer;
		rabbit::camera camera;
		rabbit::scene * scene = nullptr;

	public:
		//void attach_to_window_id(int id);
		view(rabbit::scene * scene) : scene(scene) 
		{
			drawer.init_opengl_context();
		}

		void clean() 
		{
			drawer.clean(0.3,0,0.3,0);
		}

		void draw_line_strip(
				const std::vector<vec3f>& lines, 
				const rabbit::mat4f& model_matrix
		) 
		{
			int WIDTH = 1600, HEIGHT = 800;
   			float aspect = (float)WIDTH / (float)HEIGHT;
			auto camera_projective = rabbit::opengl_perspective(
					rabbit::deg(100) / aspect, aspect, 0.1, 200);
			auto camera_position = camera.view_matrix();

			drawer.draw_points3d(
				igris::array_view<rabbit::vec3f>(
					(rabbit::vec3f*)lines.data(), lines.size()),
				GL_LINE_STRIP,
				model_matrix,
				camera_position,
				camera_projective
			);
		}
	};

	class scene 
	{
	public:
		std::list<std::shared_ptr<view>> views;
		std::list<drawable_object*> objects;

	public:
		std::shared_ptr<view> create_view() 
		{
			std::shared_ptr<view> view = std::make_shared<rabbit::view>(this);
			views.push_back(view);	
			return view;
		}

		void update() 
		{
			for(auto& v : views) 
			{
				v->clean();        
				for (auto& obj : objects) 
				{
					obj->draw_on(*v);
				}
			}
		}

		void add_object(drawable_object* obj) 
		{
			objects.push_back(obj);
		}
	};



	class polyline_drawable_object : public drawable_object
	{
		std::vector<vec3f> points;

	public:
		polyline_drawable_object(const std::vector<vec3f>& points) 
			: points(points) 
		{}

		void draw_on(rabbit::view& view) override
		{
			view.draw_line_strip(points, pose.to_mat4());
		}
	};


}

#endif