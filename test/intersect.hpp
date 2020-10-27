#include <rabbit/intersect.h>

LT_BEGIN_TEST(rabbit_test_suite, intersect)
{
	int sts;

	auto lin = rabbit::segm2(
	               rabbit::vec2(0, 2),
	               rabbit::vec2(-2, 0)
	           );

	LT_CHECK(fabs(lin.line_equation().subs_x(0) - 2) < 1e-5);
	LT_CHECK(fabs(lin.line_equation().subs_x(-1) - 1) < 1e-5);
	LT_CHECK(fabs(lin.line_equation().subs_x(-2) - 0) < 1e-5);

	LT_CHECK(fabs(fabs(lin.line_equation().a / lin.line_equation().b) - 1) < 1e-5);

	auto lin2 = rabbit::segm2(
	                rabbit::vec2(-2, 1),
	                rabbit::vec2(0, 1)
	            );

	rabbit::vec2 pnt;
	sts = intersect_point_segm2_segm2(
	          &lin,
	          &lin2,
	          &pnt
	      );

	PRINT(pnt);

	LT_CHECK_EQ(sts, 1);
	LT_CHECK(fabs(pnt.x + 1) < 1e-5);
	LT_CHECK(fabs(pnt.y - 1) < 1e-5);

	lin2 = rabbit::segm2(
	           rabbit::vec2(-2, 2),
	           rabbit::vec2(0, 0)
	       );

	sts = intersect_point_segm2_segm2(
	          &lin,
	          &lin2,
	          &pnt
	      );

	LT_CHECK_EQ(sts, 1);
}
LT_END_TEST(intersect)

LT_BEGIN_TEST(rabbit_test_suite, polysegment_intersect)
{
	linalg::vec<r_float, 2> _psegm[] =
	{
		{0, 0},
		{0, 10},
		{10, 10},
		{10, 0},
		{0, 0},
	};

	linalg::vec<r_float, 2> ipnts[10];

	rabbit::segm2 segm({-1,0}, {10, 11});
	rabbit::segm2 segm0({-1,-1}, {11, 11});
	rabbit::segm2 segm1({0,0}, {10, 10});
	rabbit::polysegm2 psegm(_psegm, 5);

	int retcount = rabbit::intersect_points_segm2_polysegm2(&segm, &psegm, ipnts); 
	LT_CHECK_EQ(retcount, 2);
	LT_CHECK(linalg::length(ipnts[0] - linalg::vec<r_float,2>(0,1)) < 1e-5);
	LT_CHECK(linalg::length(ipnts[1] - linalg::vec<r_float,2>(9,10)) < 1e-5);

	retcount = rabbit::intersect_points_segm2_polysegm2(&segm0, &psegm, ipnts); 
	LT_CHECK_EQ(retcount, 2);
	LT_CHECK(linalg::length(ipnts[0] - linalg::vec<r_float,2>(0,0)) < 1e-5);
	LT_CHECK(linalg::length(ipnts[1] - linalg::vec<r_float,2>(10,10)) < 1e-5);

	retcount = rabbit::intersect_points_segm2_polysegm2(&segm1, &psegm, ipnts); 
	LT_CHECK_EQ(retcount, 2);
	LT_CHECK(linalg::length(ipnts[0] - linalg::vec<r_float,2>(0,0)) < 1e-5);
	LT_CHECK(linalg::length(ipnts[1] - linalg::vec<r_float,2>(10,10)) < 1e-5);
}
LT_END_TEST(polysegment_intersect)
