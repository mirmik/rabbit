#include <doctest/doctest.h>
#include <rabbit/nd/deltazone.h>
#include <nos/print.h>

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

TEST_CASE("deltazone")
{
	rabbit::nd::deltacloud deltacloud;

	deltacloud.set_zone(
	{
		{ -10, 0, 10},
		{ -20, 0, 20},
		{ -30, 0, 30}
	});

	deltacloud.set_deltas(igris::ndarray<rabbit::nd::vector>
	{
		{rabbit::nd::vector{ -1, 1, 0,}, rabbit::nd::vector{0, 1, 0}, rabbit::nd::vector{1, 1, 0}},
		{rabbit::nd::vector{ -1, 0, 0,}, rabbit::nd::vector{0, 0, 0}, rabbit::nd::vector{1, 0, 0}},
		{rabbit::nd::vector{ -1, -1, 0,}, rabbit::nd::vector{0, -1, 0}, rabbit::nd::vector{1, -1, 0}},
	});

	SUBCASE("deltas")
	{
		CHECK_EQ(deltacloud.deltas()({0, 0}), ralgo::vector<double> { -1, 1, 0});
		CHECK_EQ(deltacloud.deltas()({0, 1}), ralgo::vector<double> {0, 1, 0});
		CHECK_EQ(deltacloud.deltas()({0, 2}), ralgo::vector<double> {1, 1, 0});
		CHECK_EQ(deltacloud.deltas()({1, 0}), ralgo::vector<double> { -1, 0, 0});
		CHECK_EQ(deltacloud.deltas()({1, 1}), ralgo::vector<double> {0, 0, 0});
		CHECK_EQ(deltacloud.deltas()({1, 2}), ralgo::vector<double> {1, 0, 0});
		CHECK_EQ(deltacloud.deltas()({2, 0}), ralgo::vector<double> { -1, -1, 0});
		CHECK_EQ(deltacloud.deltas()({2, 1}), ralgo::vector<double> {0, -1, 0});
		CHECK_EQ(deltacloud.deltas()({2, 2}), ralgo::vector<double> {1, -1, 0});
	}

	SUBCASE("point_indices")
	{
		auto idxs = deltacloud.grid().point_in_cell_indices({7, 15, 25});
		CHECK_EQ(idxs, ralgo::vector<int> {1, 1, 1});

		idxs = deltacloud.grid().point_in_cell_indices({ -7, -15, -25});
		CHECK_EQ(idxs, ralgo::vector<int> {0, 0, 0});
	}

	SUBCASE("cellzone")
	{
		auto idxs = deltacloud.grid().point_in_cell_indices({ -7, 15, -25});
		auto cell = deltacloud.grid().cellzone(idxs);

		CHECK_EQ(cell.maxs, ralgo::vector<double>{0,20,0});
		CHECK_EQ(cell.mins, ralgo::vector<double>{-10,0,-30});

		CHECK_EQ(idxs, ralgo::vector<int> {0, 1, 0});
	}
}