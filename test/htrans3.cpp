#include <rabbit/space/htrans3.h>
#include <doctest/doctest.h>

TEST_CASE("htrans3")
{
	rabbit::htrans3<double> tr0
	{
		{sin(M_PI / 4), 0, 0, cos(M_PI / 4)},
		{0, 0, 0}
	};

	rabbit::htrans3<double> tr1
	{
		{sin(-M_PI / 4), 0, 0, cos(-M_PI / 4)},
		{0, 0, 0}
	};

	auto tr01 = tr0 * tr1;

	CHECK_EQ(tr01, rabbit::htrans3<double>());




	rabbit::htrans3<double> tr2
	{
		{0, 0, 0, 1},
		{0, 10, 0}
	};

	rabbit::htrans3<double> tr3
	{
		{0, 0, 0, 1},
		{0, -10, 0}
	};

	auto tr23 = tr2 * tr3;

	CHECK_EQ(tr23, rabbit::htrans3<double>());


	rabbit::htrans3<double> tr4
	{
		{0, 0, 0, 1},
		{-10, 0, 0}
	};

	rabbit::htrans3<double> tr5
	{
		{0, 0, sin(M_PI/4), cos(M_PI/4)},
		{0, 0, 0}
	};

	rabbit::htrans3<double> tr6
	{
		{0, 0, 0, 1},
		{0, -10, 0}
	};

	auto tr56 = tr5 * tr6;
	auto tr456 = tr4 * tr5 * tr6;

	CHECK(linalg::length(tr456.lin - linalg::vec<double,3>(0,0,0)) < 1e-5);

	CHECK_EQ(tr0.inverse(), tr1);
	CHECK_EQ(
		tr2.inverse(), 
		rabbit::htrans3<double>{{0,0,0,1},{0,-10,0}});

	CHECK_EQ(tr0.to_screw(), rabbit::screw<double,3>{{M_PI/2,0,0},{0,0,0}});
}
