#include <rabbit/intersect.h>

LT_BEGIN_TEST(rabbit_test_suite, intersect)
{
	auto lin =rabbit::line2::by_pntdir(
		rabbit::vec2(-1,1), 
		rabbit::vec2(1,1)
	);

	LT_CHECK(fabs(lin.subs_x(0) - 2) < 1e-5);
	LT_CHECK(fabs(lin.subs_x(-1) - 1) < 1e-5);
	LT_CHECK(fabs(lin.subs_x(-2) - 0) < 1e-5);

	LT_CHECK(fabs(lin.a + sqrt(2)/2) < 1e-5);
	LT_CHECK(fabs(lin.b - sqrt(2)/2) < 1e-5);
	LT_CHECK(fabs(lin.c + sqrt(2)) < 1e-5);

	auto lin2 =rabbit::line2::by_pntdir(
		rabbit::vec2(1,1), 
		rabbit::vec2(-1,1)
	);

	auto pnt = intersect_point_line2_line2(
	    lin,
	    lin2
	);

	LT_CHECK(fabs(pnt.x - 0) < 1e-5);
	LT_CHECK(fabs(pnt.y - 2) < 1e-5);

	lin2 =rabbit::line2::by_pntdir(
		rabbit::vec2(2,1), 
		rabbit::vec2(-1,1)
	);

	pnt = intersect_point_line2_line2(
	    lin,
	    lin2
	);
}
LT_END_TEST(intersect)