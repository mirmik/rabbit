#include <doctest/doctest.h>
#include <rabbit/nd/deltazone.h>
#include <nos/print.h>

TEST_CASE("deltazone") 
{
	rabbit::nd::deltacloud deltacloud;

	deltacloud.set_zone({
		{-10,0,10},
		{-20,0,20},
		{-30,0,30}
	});

	auto ndindexes = rabbit::nd::binary_hypercube_vertices(3);
	CHECK_EQ(ndindexes[0], ralgo::vector<int>{0,0,0});
	CHECK_EQ(ndindexes[1], ralgo::vector<int>{0,0,1});
	CHECK_EQ(ndindexes[2], ralgo::vector<int>{0,1,0});
	CHECK_EQ(ndindexes[3], ralgo::vector<int>{0,1,1});
	CHECK_EQ(ndindexes[4], ralgo::vector<int>{1,0,0});
	CHECK_EQ(ndindexes[5], ralgo::vector<int>{1,0,1});
	CHECK_EQ(ndindexes[6], ralgo::vector<int>{1,1,0});
	CHECK_EQ(ndindexes[7], ralgo::vector<int>{1,1,1});

	ndindexes = rabbit::nd::multidim_cell_indices({3,6,1});
	CHECK_EQ(ndindexes[0], ralgo::vector<int>{3,6,1});
	CHECK_EQ(ndindexes[1], ralgo::vector<int>{3,6,2});
	CHECK_EQ(ndindexes[2], ralgo::vector<int>{3,7,1});
	CHECK_EQ(ndindexes[3], ralgo::vector<int>{3,7,2});
	CHECK_EQ(ndindexes[4], ralgo::vector<int>{4,6,1});
	CHECK_EQ(ndindexes[5], ralgo::vector<int>{4,6,2});
	CHECK_EQ(ndindexes[6], ralgo::vector<int>{4,7,1});
	CHECK_EQ(ndindexes[7], ralgo::vector<int>{4,7,2});
}