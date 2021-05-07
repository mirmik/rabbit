#include <rabbit/prim2.h>
#include <doctest/doctest.h>

#include <nos/print.h>
#include <rabbit/math/minbracket.h>

class sqrfunc : public rabbit::function 
{
	int value(rabbit::real p, rabbit::real * result) override
	{
		*result = p * p;
		return 0;
	}
};

TEST_CASE("minbracket")
{
	sqrfunc foo;

	rabbit::minimize_bracket bracket(&foo, 5, 6);
	bracket.doit();

	rabbit::minimize_gold mingold(bracket.a, bracket.b);
}