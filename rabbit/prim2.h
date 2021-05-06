#ifndef RABBIT_PRIM2_H
#define RABBIT_PRIM2_H

#include <rabbit/linalg.h>
#include <nos/fprint.h>

namespace rabbit
{
	template <class T>
	class equation_curve2 
	{
		virtual T subs(T x, T y) = 0;
	};

	template <class T>
	class line2eq
	{
	public:
		T a, b, c;

		line2eq(T a, T b, T c)
			: a(a), b(b), c(c)
		{}

		T subs(T x, T y) 
		{
			return a*x + b*y + c;
		}

		static
		line2eq from_points(linalg::vec<T, 2> p1, linalg::vec<T, 2> p2)
		{
			linalg::vec<T, 2> d = p2 - p1;

			T dx = d.x;
			T dy = d.y;
			T x1 = p1.x;
			T y1 = p1.y;
			T x2 = p2.x;
			T y2 = p2.y;

			T a = -dy;
			T b =  dx;
			T c = x1 * y2 - y1 * x2;

			return { a, b, c };
		}

		static
		line2eq from_point_and_vector(linalg::vec<T, 2> pnt, linalg::vec<T, 2> vec)
		{
			auto x = pnt.x;
			auto y = pnt.y;

			auto a = - vec.y;
			auto b =   vec.x;
			auto c = - (a * x + b * y);

			return line2eq(a, b, c);
		}

		T subs_x(T x)
		{
			return (-a * x - c) / b;
		}

		T subs(linalg::vec<T, 2> pnt) const
		{
			return pnt.x * a + pnt.y * b + c;
		}

		ssize_t print_to(nos::ostream & os) const
		{
			return nos::fprint_to(os, "({}x+{}y+{}=0)", a, b, c);
		}

		bool equal(const line2eq & oth) 
		{
			// TODO
			return true;
		}
	};

	template <class T>
	class segm2
	{
	public:
		linalg::vec<T, 2> apnt;
		linalg::vec<T, 2> bpnt;

	public:
		segm2() {}

		segm2& operator = (const segm2& oth) = default;

		segm2(linalg::vec<T, 2> apnt, linalg::vec<T, 2> bpnt)
			: apnt(apnt), bpnt(bpnt) {}

		segm2 transformed(const trans2& trsf) const
		{
			return
			{
				trsf.transform_point(apnt),
				trsf.transform_point(bpnt)
			};
		}

		line2eq<T> line_equation() const
		{
			return line2eq<T>::from_points(apnt, bpnt);
		}

		ssize_t print_to(nos::ostream & os) const
		{
			return nos::fprint_to(os, "({},{})", apnt, bpnt);
		}
	};

	template <class T>
	class polysegm2
	{
	public:
		linalg::vec<T, 2> * pnts;
		int pnts_count;

	public:

		polysegm2()
			: pnts(nullptr)
		{}

		polysegm2& operator=(const polysegm2&) = default;

		polysegm2(linalg::vec<T, 2> * pnts, int pnts_count)
			: pnts(pnts), pnts_count(pnts_count)
		{}
	};
}

#endif