#include <nos/print.h>
#include <igris/math/deg.h>
#include <rabbit/trans/trans2.h>

int main()
{
	rabbit::trans2 h(deg(90), {10,10});

	nos::println(h);
	nos::println(rabbit::trans2(deg(90), {})* h);
	nos::println(h * h);
}