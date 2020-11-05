#include <rabbit/space/screw.h>
#include <rabbit/space/htrans3.h>

template <class T>
rabbit::screw<T,3> rabbit::screw<T,3>::rotate_by(const htrans3<T>& tr) 
{
	return 
	{
		tr.rotate(ang),
		tr.rotate(lin)
	};
}

auto ptr1 = &rabbit::screw<double,3>::rotate_by;
auto ptr2 = &rabbit::screw<float,3>::rotate_by;

//static void __template_instance() 
//{
	rabbit::screw<float,3> a;
	rabbit::screw<double,3> b;
	rabbit::screw<float,2> c;
	rabbit::screw<double,2> d;
//}