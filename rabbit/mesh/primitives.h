#include <rabbit/mesh/mesh.h>

namespace rabbit 
{
	rabbit::mesh<float> sphere_mesh(float rad, int x=10, int y=10);
	rabbit::mesh<float> box_mesh(float x, float y, float z);
}