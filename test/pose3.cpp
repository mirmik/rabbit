#include <doctest/doctest.h>
#include <rabbit/space/pose3.h>

#include <iostream>
#include <igris/dprint.h>

namespace linalg { using linalg::ostream_overloads::operator <<; }

TEST_CASE("pose3") 
{
	rabbit::screw3<double> a = { {0,0,1}, {0,0,0} };	
	rabbit::pose3<double> b = rabbit::mov3<double>({1,0,0});

	auto c = a.kinematic_carry(b); 

	CHECK_EQ(c, rabbit::screw3<double>{{0,0,1},{1,0,0}});
} 