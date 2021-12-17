#include <rabbit/nd/named_cartesian_correction.h>
#include <doctest/doctest.h>

TEST_CASE("named_cartesian_correction") 
{
	rabbit::nd::named_cartesian_correction correction;

	correction.set_full_axes_names({"X", "Y", "Z", "A"});
	correction.set_zone_names({"X", "Y"});
	correction.set_deltas_names({"Z"});

	correction.set_zone({
		{0,1,2},
		{0,1,2}
	});

	correction.set_deltas({
		{ralgo::vector<double>{0.1}, {0.2}, {0.1}},
		{{0.1}, {1, 1}, {-0.1}},
		{{-0.1}, {-0.2}, {0.3}}
	});	


}