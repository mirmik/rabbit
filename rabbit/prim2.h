#ifndef RABBIT_PRIM2_H
#define RABBIT_PRIM2_H

#include <rabbit/linalg.h>
#include <nos/fprint.h>

namespace rabbit
{
	class line2
	{
	public:
		r_float a, b, c;

		line2(r_float a, r_float b, r_float c) 
			: a(a), b(b), c(c)
		{}

		static
		line2 by_pntdir(vec2 pnt, vec2 dir)
		{
			dir = normalize(dir);

			r_float dx = dir.x;
			r_float dy = dir.y;
			r_float x1 = pnt.x;
			r_float y1 = pnt.y;
			r_float x2 = x1 + dx;
			r_float y2 = y1 + dy;

			r_float a = -dy;
			r_float b =  dx;
			r_float c = x1*y2 - y1*x2;

			return { a, b, c };
		}

		r_float subs_x(r_float x)
		{
			return (-a*x - c) / b;
		}

		ssize_t print_to(nos::ostream & os) const
		{
			return nos::fprint_to(os, "({}x+{}y+{}=0)", a, b, c);
		}
	};

	class segm2
	{
		vec2 apnt;
		vec2 bpnt;

		segm2(vec2 apnt, vec2 bpnt) : apnt(apnt), bpnt(bpnt) {}

		segm2 transformed(const trans2& trsf)
		{
			return
			{
				trsf.transform_point(apnt),
				trsf.transform_point(bpnt)
			};
		}
	};
}

#endif