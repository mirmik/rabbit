#include <doctest/doctest.h>
#include <rabbit/nd/cartesian_correction.h>
#include <nos/print.h>

TEST_CASE("cartesian_correction.perpendicular") 
{
	rabbit::nd::cartesian_correction cartesian_correction;

	cartesian_correction.set_fulldim(3);

	cartesian_correction.set_zone(
	{
		{ -10, 0, 10}
	});

	cartesian_correction.set_deltas(
	{
		rabbit::nd::vector{0.1}, {0.2}, {0.3}
	});

	cartesian_correction.set_delta_to_full_indexes({
		{0, 2},
	});

	cartesian_correction.set_grid_to_full_indexes({
		{0, 1},
	});

	rabbit::nd::vector point {0,5,0};
	auto corrected = cartesian_correction.corrected_point(point);

	CHECK_EQ(corrected, ralgo::vector<double>{0,5,0.25});
}

TEST_CASE("cartesian_correction.same") 
{
	rabbit::nd::cartesian_correction cartesian_correction;

	cartesian_correction.set_fulldim(3);

	cartesian_correction.set_zone(
	{
		{ -10, 0, 10}
	});

	cartesian_correction.set_deltas(
	{
		rabbit::nd::vector{0.1}, {0.2}, {0.3}
	});

	cartesian_correction.set_delta_to_full_indexes({
		{0, 1},
	});

	cartesian_correction.set_grid_to_full_indexes({
		{0, 1},
	});

	rabbit::nd::vector point {0,5,0};
	auto corrected = cartesian_correction.corrected_point(point);

	CHECK_EQ(corrected, ralgo::vector<double>{0,5.25,0});
}

TEST_CASE("cartesian_correction.same") 
{
	rabbit::nd::cartesian_correction cartesian_correction;

	cartesian_correction.set_fulldim(3);

	cartesian_correction.set_zone(
	{
		{ -10, 0, 10}
	});

	cartesian_correction.set_deltas(
	{
		rabbit::nd::vector{0.1}, {0.2}, {0.3}
	});

	cartesian_correction.set_delta_to_full_indexes({
		{0, 1},
	});

	cartesian_correction.set_grid_to_full_indexes({
		{0, 2},
	});

	rabbit::nd::vector point {5,0,0};
	auto corrected = cartesian_correction.corrected_point(point);

	CHECK_EQ(corrected, ralgo::vector<double>{5,0.2,0});
}

TEST_CASE("binary_hypercube")
{
	auto ndindexes = rabbit::nd::binary_hypercube_vertices(3);
	CHECK_EQ(ndindexes[0], ralgo::vector<int> {0, 0, 0});
	CHECK_EQ(ndindexes[1], ralgo::vector<int> {0, 0, 1});
	CHECK_EQ(ndindexes[2], ralgo::vector<int> {0, 1, 0});
	CHECK_EQ(ndindexes[3], ralgo::vector<int> {0, 1, 1});
	CHECK_EQ(ndindexes[4], ralgo::vector<int> {1, 0, 0});
	CHECK_EQ(ndindexes[5], ralgo::vector<int> {1, 0, 1});
	CHECK_EQ(ndindexes[6], ralgo::vector<int> {1, 1, 0});
	CHECK_EQ(ndindexes[7], ralgo::vector<int> {1, 1, 1});
}

TEST_CASE("binary_hypercube")
{
	auto ndindexes = rabbit::nd::binary_hypercube_vertices(1);
	CHECK_EQ(ndindexes[0], ralgo::vector<int> {0});
	CHECK_EQ(ndindexes[1], ralgo::vector<int> {1});
}

TEST_CASE("multidim_cell_indices")
{
	auto ndindexes = rabbit::nd::multidim_cell_indices({3, 6, 1});
	CHECK_EQ(ndindexes[0], ralgo::vector<int> {3, 6, 1});
	CHECK_EQ(ndindexes[1], ralgo::vector<int> {3, 6, 2});
	CHECK_EQ(ndindexes[2], ralgo::vector<int> {3, 7, 1});
	CHECK_EQ(ndindexes[3], ralgo::vector<int> {3, 7, 2});
	CHECK_EQ(ndindexes[4], ralgo::vector<int> {4, 6, 1});
	CHECK_EQ(ndindexes[5], ralgo::vector<int> {4, 6, 2});
	CHECK_EQ(ndindexes[6], ralgo::vector<int> {4, 7, 1});
	CHECK_EQ(ndindexes[7], ralgo::vector<int> {4, 7, 2});
}

TEST_CASE("cartesian_correction")
{
	rabbit::nd::cartesian_correction cartesian_correction;

	cartesian_correction.set_zone(
	{
		{ -10, 0, 10},
		{ -20, 0, 20},
		{ -30, 0, 30}
	});

	cartesian_correction.set_deltas(igris::ndarray<rabbit::nd::vector>
	{
		{
			{rabbit::nd::vector{ -1, 1, 0,}, rabbit::nd::vector{0, 1, 0}, rabbit::nd::vector{1, 1, 0}},
			{rabbit::nd::vector{ -1, 0, 0,}, rabbit::nd::vector{0, 0, 0}, rabbit::nd::vector{1, 0, 0}},
			{rabbit::nd::vector{ -1, -1, 0,}, rabbit::nd::vector{0, -1, 0}, rabbit::nd::vector{1, -1, 0}},
		},
		{
			{rabbit::nd::vector{ -1, 1, 0,}, rabbit::nd::vector{0, 1, 0}, rabbit::nd::vector{1, 1, 0}},
			{rabbit::nd::vector{ -1, 0, 0,}, rabbit::nd::vector{0, 0, 0}, rabbit::nd::vector{1, 0, 0}},
			{rabbit::nd::vector{ -1, -1, 0,}, rabbit::nd::vector{0, -1, 0}, rabbit::nd::vector{1, -1, 0}},
		},
		{
			{rabbit::nd::vector{ -1, 1, 0,}, rabbit::nd::vector{0, 1, 0}, rabbit::nd::vector{1, 1, 0}},
			{rabbit::nd::vector{ -1, 0, 0,}, rabbit::nd::vector{0, 0, 0}, rabbit::nd::vector{1, 0, 0}},
			{rabbit::nd::vector{ -1, -1, 0,}, rabbit::nd::vector{0, -1, 0}, rabbit::nd::vector{1, -1, 0}},
		}
	});

	SUBCASE("deltas")
	{
		CHECK_EQ(cartesian_correction.deltas()({0, 0, 0}), ralgo::vector<double> { -1, 1, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 0, 1}), ralgo::vector<double> {0, 1, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 0, 2}), ralgo::vector<double> {1, 1, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 1, 0}), ralgo::vector<double> { -1, 0, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 1, 1}), ralgo::vector<double> {0, 0, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 1, 2}), ralgo::vector<double> {1, 0, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 2, 0}), ralgo::vector<double> { -1, -1, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 2, 1}), ralgo::vector<double> {0, -1, 0});
		CHECK_EQ(cartesian_correction.deltas()({0, 2, 2}), ralgo::vector<double> {1, -1, 0});
	}

	SUBCASE("point_indices")
	{
		auto idxs = cartesian_correction.grid().point_in_cell_indices({7, 15, 25});
		CHECK_EQ(idxs, ralgo::vector<int> {1, 1, 1});

		idxs = cartesian_correction.grid().point_in_cell_indices({ -7, -15, -25});
		CHECK_EQ(idxs, ralgo::vector<int> {0, 0, 0});
	}

	SUBCASE("cellzone")
	{
		auto idxs = cartesian_correction.grid().point_in_cell_indices({ -7, 15, -25});
		auto cell = cartesian_correction.grid().cellzone(idxs);

		CHECK_EQ(cell.maxs, ralgo::vector<double> {0, 20, 0});
		CHECK_EQ(cell.mins, ralgo::vector<double> { -10, 0, -30});

		CHECK_EQ(idxs, ralgo::vector<int> {0, 1, 0});
		CHECK_EQ(cell.lerpcoeffs({ -5, 10, -15}), ralgo::vector<double> {0.5, 0.5, 0.5});
	}
}
