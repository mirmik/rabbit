#include <nos/print.h>
#include <igris/math/deg.h>
#include <rabbit/space/htrans.h>

int main()
{
	rabbit::htrans2 h(deg(90), {10,10});

	nos::println(h);
	nos::println(rabbit::htrans2(deg(90), {})* h);
	nos::println(h * h);
}