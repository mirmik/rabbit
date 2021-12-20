#include <rabbit/nd/named_cartesian_correction.h>
#include <doctest/doctest.h>

#include <igris/trent/json.h>

TEST_CASE("named_cartesian_correction") 
{
	auto tr = igris::json::parse(R"({
	"head": {
		"full" : [ "X", "Y", "Z"],
		"grid" : [ "X", "Y" ],
		"deltas" : [ "Z" ],
	},

	"grid" : [
		[0, 2, 3],
		[0, 1]
	],

	"deltas" : [
		[[ 0.10], [-0.22]], 
		[[-0.20], [-0.32]],
		[[ 0.28], [ 0.16]]
	]
}
)");

	auto ret = rabbit::nd::parse_correction_table(tr);

	CHECK_EQ(ret.head_full, std::vector<std::string>{ "X", "Y", "Z" });
	CHECK_EQ(ret.head_deltas, std::vector<std::string>{ "Z" });
	CHECK_EQ(ret.head_grid, std::vector<std::string>{ "X", "Y" });

	CHECK_EQ(ret.grid[0], std::vector<double>{ 0, 2, 3 });
	CHECK_EQ(ret.grid[1], std::vector<double>{ 0, 1 });

	CHECK_EQ(ret.deltas.shape(), std::vector<size_t>{3,2});
	CHECK_EQ(ret.deltas({0,0}), rabbit::nd::vector{0.1});
	CHECK_EQ(ret.deltas({1,1}), rabbit::nd::vector{-0.32});
	CHECK_EQ(ret.deltas({1,0}), rabbit::nd::vector{-0.20});
	CHECK_EQ(ret.deltas({2,1}), rabbit::nd::vector{0.16});
}