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

	rabbit::htrans3<double> tr
	{
		{0, 0, sin(M_PI / 4), cos(M_PI / 4)},
		{0, 0, 0}
	};

	rabbit::screw<double,3> aa {{10,0,0}, {0,10,10}};
	rabbit::screw<double,3> bb {{0,10,0}, {-10,0,10}};

	CHECK(length((aa.rotate_by(tr)).lin - bb.lin) < 1e-5);
	CHECK(length((aa.rotate_by(tr)).ang - bb.ang) < 1e-5);

}

TEST_CASE("htrans3_2")
{
		rabbit::htrans3<double> tr0
	{
		{sin(0.5), 0, 0, cos(0.5)},
		{0, 2, 0}
	};

	rabbit::htrans3<double> tr1
	{
		{0, sin(-0.1), 0, cos(-0.1)},
		{1, 0, 2}
	};

	rabbit::htrans3<double> tr2
	{
		{0, 0, sin(-2), cos(-2)},
		{0, 3, 1}
	};

	rabbit::htrans3<double> tr3
	{
		{0, 0, sin(M_PI/4), cos(M_PI/4)},
		{1, 0, 0}
	};

	auto tr = tr0 * tr1 * tr2;

	PRINT(tr0);
	PRINT(tr1);
	PRINT(tr2);

	PRINT(tr0 * tr1);
	PRINT(tr1 * tr2);

	PRINT(tr);
	PRINT(tr.inverse());
	PRINT(tr.inverse() * tr);
	PRINT(tr * tr.inverse());

	PRINT(tr3);
	PRINT(tr3.inverse());
}

TEST_CASE("htrans3_2")
{
		rabbit::htrans3<double> tr0
	{
		linalg::rotation_quat<double>(linalg::normalize<double,3>({1,1,1}), 2),
		{0, 2, 0}
	};

	PRINT(tr0.to_screw());
	PRINT(linalg::length(tr0.to_screw().ang));
}

TEST_CASE("htrans3_3")
{
	rabbit::htrans3<double> tr0
	{
		linalg::rotation_quat<double>({1,0,0}, M_PI/2),
		{0, 0, 0}
	};

	rabbit::htrans3<double> tr1
	{
		linalg::rotation_quat<double>({0,1,0}, M_PI/2),
		{0, 0, 0}
	};

	rabbit::htrans3<double> tr2
	{
		linalg::rotation_quat<double>({0,0,1}, M_PI/2),
		{0, 0, 0}
	};

	PRINT(tr0 * tr1 * tr2 * tr0 * tr1 * tr2);
	PRINT(tr1.inverse() * tr2 * tr1 * tr0);
}