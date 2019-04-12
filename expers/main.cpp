#include <nos/print.h>
#include <rabbit/plane.h>
#include <rabbit/curve2.h>
#include <rabbit/curve3.h>

using namespace linalg::ostream_overloads;
using namespace linalg::aliases;

int main()
{
	rabbit::plane<float> pln({0,1,0}, {0,1,1});
	rabbit::circ2<float> crv({0,1}, {0,1});
	rabbit::line2<float> l2({0,1}, {0,1});
	rabbit::line3<float> l3({0,1,1}, {0,1,2});
	nos::println(pln);
	nos::println(crv);
}