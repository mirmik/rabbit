#ifndef RABBIT_PRIM2_H
#define RABBIT_PRIM2_H

#include <rabbit/linalg.h>
#include <nos/fprint.h>

namespace rabbit
{
	class line2eq
	{
	public:
		r_float a, b, c;

		line2eq(r_float a, r_float b, r_float c) 
			: a(a), b(b), c(c)
		{}

		static
		line2 from_points(vec2 p1, vec2 p2)
		{
			vec2 d = p2 - p2;
			r_float dx = d.x;
			r_float dy = d.y;
			r_float x1 = p1.x;
			r_float y1 = p2.y;
			r_float x2 = p2.x;
			r_float y2 = p2.y;

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

		line2eq line_equation() 
		{
			return line2eq::from_points(apnt, bpnt);
		} 
	};

	class polysegm2 
	{
		vec2 * pnts;
		int pnts_count;

	public:
		polysegm2(vec2 * pnts, int pnts_count) 
			: pnts(pnts), pnts_count(pnts_count)
		{}
	};
}

#endif