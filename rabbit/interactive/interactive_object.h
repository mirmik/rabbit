#ifndef RABBIT_INTERACTIVE_OBJECT_H
#define RABBIT_INTERACTIVE_OBJECT_H

#include <memory>
#include <rabbit/mesh/mesh.h>
#include <rabbit/meshline.h>

namespace rabbit 
{
	class interactive_object 
	{
		pose3<real> pose;

		std::shared_ptr<rabbit::mesh<float>> get_mesh();
		std::shared_ptr<rabbit::meshline> get_lines();
	};
}

#endif