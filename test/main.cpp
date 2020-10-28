#include "littletest.hpp"
#include <string>

LT_BEGIN_SUITE(rabbit_test_suite)
	void set_up()
	{}

	void tear_down()
	{}
LT_END_SUITE(rabbit_test_suite)

#include "intersect.hpp"

LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()