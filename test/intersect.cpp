#include <rabbit/intersect.h>
#include <doctest/doctest.h>

TEST_CASE("intersect")
{
	int sts;

	auto lin = rabbit::segm2(
	               rabbit::vec2(0, 2),
	               rabbit::vec2(-2, 0)
	           );

	CHECK(fabs(lin.line_equation().subs_x(0) - 2) < 1e-5);
	CHECK(fabs(lin.line_equation().subs_x(-1) - 1) < 1e-5);
	CHECK(fabs(lin.line_equation().subs_x(-2) - 0) < 1e-5);

	CHECK(fabs(fabs(lin.line_equation().a / lin.line_equation().b) - 1) < 1e-5);

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

	CHECK_EQ(sts, 1);
	CHECK(fabs(pnt.x + 1) < 1e-5);
	CHECK(fabs(pnt.y - 1) < 1e-5);

	lin2 = rabbit::segm2(
	           rabbit::vec2(-2, 2),
	           rabbit::vec2(0, 0)
	       );

	sts = intersect_point_segm2_segm2(
	          &lin,
	          &lin2,
	          &pnt
	      );

	CHECK_EQ(sts, 1);
}

TEST_CASE("polysegment_intersect")
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

	int retcount;

	retcount = rabbit::intersect_points_segm2_polysegm2(&segm, &psegm, ipnts); 
	CHECK_EQ(retcount, 2);
	CHECK(linalg::length(ipnts[0] - linalg::vec<r_float,2>(0,1)) < 1e-5);
	CHECK(linalg::length(ipnts[1] - linalg::vec<r_float,2>(9,10)) < 1e-5);

	retcount = rabbit::intersect_points_segm2_polysegm2(&segm0, &psegm, ipnts); 
	CHECK_EQ(retcount, 2);
	CHECK(linalg::length(ipnts[0] - linalg::vec<r_float,2>(0,0)) < 1e-5);
	CHECK(linalg::length(ipnts[1] - linalg::vec<r_float,2>(10,10)) < 1e-5);

	retcount = rabbit::intersect_points_segm2_polysegm2(&segm1, &psegm, ipnts); 
	CHECK_EQ(retcount, 2);
	CHECK(linalg::length(ipnts[0] - linalg::vec<r_float,2>(0,0)) < 1e-5);
	CHECK(linalg::length(ipnts[1] - linalg::vec<r_float,2>(10,10)) < 1e-5);
}
