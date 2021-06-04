#ifndef RABBIT_INTERACTIVE_OBJECT_H
#define RABBIT_INTERACTIVE_OBJECT_H

#include <memory>
#include <rabbit/mesh.h>
#include <rabbit/meshline.h>

namespace rabbit 
{
	class interactive_object 
	{
		pose3 pose;

		std::shared_ptr<rabbit::mesh> get_mesh();
		std::shared_ptr<rabbit::meshline> get_lines();
	};
}

#endif