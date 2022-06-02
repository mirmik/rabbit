#ifndef RABBIT_CAMERA_H
#define RABBIT_CAMERA_H

#include <ralgo/space/pose3.h>

namespace rabbit
{
	class camera
	{
		vec3f _eye;
		vec3f _dir;
		vec3f _up;

	public:
		camera() : _eye{0, 0, 0}, _dir(1, 0, 0), _up(0, 0, 1)
		{
			correct_up();
		}

		camera(
		    const vec3f & eye,
		    const vec3f & target,
		    const vec3f & up = {0, 0, 1}
		)
			: _eye(eye), _dir(normalize(eye - target)), _up(normalize(up))
		{
			correct_up();
		}

		vec3f right()
		{
			return cross(_up, _dir);
		}

		void correct_up()
		{
			auto _right = right();
			
			if (length(_right) < 1e-5)
			{
				if (_dir.z > 0.99)
					_up = {1, 0, 0};
				else
					_up = {0, 0, 1};
				_right = right();
			}

			_up = cross(_dir, _right);
			_up = normalize(_up);
		}

		void set_eye(const vec3f& vec) { _eye = vec; }
		void set_eye(const vec3& vec) { _eye = vec3f{ (float)vec.x, (float)vec.y, (float)vec.z }; }
		void set_dir(const vec3f& vec) { _dir = normalize(vec); }
		void set_target(const vec3f& target)
		{
			_dir = normalize(_eye - target);
			correct_up();
		}

		mat4f view_rotation_matrix()
		{
			vec3f& D = _dir;
			vec3f& U = _up;
			vec3f  R = normalize(cross(_up, _dir));

			return
			{
				{R.x, U.x, D.x, 0},
				{R.y, U.y, D.y, 0},
				{R.z, U.z, D.z, 0},
				{0, 0, 0, 1}
			};
		}

		mat4f view_translation_matrix()
		{
			vec3f& C = _eye;

			return
			{
				{  1.f,  0.f,  0.f, 0.f},
				{  0.f,  1.f,  0.f, 0.f},
				{  0.f,  0.f,  1.f, 0.f},
				{ -C.x, -C.y, -C.z, 1.f}
			};
		}

		mat4f view_matrix()
		{
			return mul(view_rotation_matrix(), view_translation_matrix());
		}
	};
}

#endif