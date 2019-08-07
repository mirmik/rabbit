#ifndef RABBIT_PHYSICS_BODY_H
#define RABBIT_PHYSICS_BODY_H

namespace rabbit 
{
	struct body 
	{
		rabbit::trans3 position;
		rabbit::inertia3 inertia;
	};
}

#endif