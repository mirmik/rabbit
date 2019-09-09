#include <nos/print.h>
#include <igris/math/deg.h>

#include <rabbit/space/symmetric_matrix.h>

#include <nos/print.h>

int main()
{
	rabbit::symmetric_matrix<double,3> a, b;

	nos::println(a);
	nos::println(b);
}