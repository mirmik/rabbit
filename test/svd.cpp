#include <doctest/doctest.h>

#include <nos/print.h>
#include <ralgo/linalg/svd.h>

TEST_CASE("svd")
{
	float angle = M_PI/4;
	float arr[] = { 
		cos(angle)/4,sin(angle)/2,
		sin(angle)/4,-cos(angle)/2 };
	auto svdmat = ralgo::matrix_view_ro<float>(arr, 2, 2);
	auto svd = ralgo::svd(svdmat);

	nos::println("U:");
	nos::print_matrix(svd.u);

	nos::println("V:");
	nos::print_matrix(svd.v);

	nos::println("W:");
	nos::print_list(svd.w);
}