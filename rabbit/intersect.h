#ifndef RABBIT_INTERSECT_H
#define RABBIT_INTERSECT_H

#include <rabbit/linalg.h>
#include <rabbit/types.h>
#include <rabbit/prim2.h>

namespace rabbit
{

	class intersect_node
	{
		bool is_interval;
		r_float aparam0;
		r_float aparam1;
		r_float bparam0;
		r_float bparam1;
	};

	static inline
	rabbit::vec2 intersect_point_line2_line2(
	    const rabbit::line2eq& alin,
	    const rabbit::line2eq& blin,
	    int
	)
	{
		linalg::vec<r_float, 3> a =
		{ alin.a, alin.b, alin.c };
		linalg::vec<r_float, 3> b =
		{ blin.a, blin.b, blin.c };

		PRINT(a);
		PRINT(b);
		linalg::vec<r_float, 3> r = linalg::cross(a, b);

		BUG_ON(fabs(r.z) < 1e-5);

		PRINT(r);

		return { r.x / r.z, r.y / r.z };
	}


	static inline
	int intersect_point_segm2_segm2(
	    const segm2 * segment1,
	    const segm2 * segment2,
	    vec2        * out_intersection,
	    float epsilon = r_epsilon
	)
	{
		vec2 start1 = segment1->apnt;
		vec2 start2 = segment2->apnt;
		vec2 end1 = segment1->bpnt;
		vec2 end2 = segment2->bpnt;

		vec2 dir1 = end1 - start1;
		vec2 dir2 = end2 - start2;

		//nos::println("intersect_segm2_segm2", *segment1, *segment2);

		//считаем уравнения прямых проходящих через отрезки
		//float a1 = -dir1.y;
		//float b1 = +dir1.x;
		//float d1 = -(a1*start1.x + b1*start1.y);

		//float a2 = -dir2.y;
		//float b2 = +dir2.x;
		//float d2 = -(a2*start2.x + b2*start2.y);

		line2eq eq1 = segment1->line_equation();
		line2eq eq2 = segment2->line_equation();

		// подставляем концы отрезков, для выяснения в каких полуплоскотях они
		// точки первого отрезка подставляются во второе уравнение,
		// а второго в первое.
		r_float seg1_line2_start = eq2.subs(segment1->apnt);
		r_float seg1_line2_end = eq2.subs(segment1->bpnt);

		r_float seg2_line1_start = eq1.subs(segment2->apnt);
		r_float seg2_line1_end = eq1.subs(segment2->bpnt);

		// если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
		// Проверяем с учетом точности. Если отрезок подходит к другому ближе, чем на эпсилон, защитывается пересечение.
		if (seg1_line2_start * seg1_line2_end >= epsilon || seg2_line1_start * seg2_line1_end >= epsilon) 
		{
			//nos::println("result: none");
			return 0;
		}

		// Из пропорции расстояний находим параметр в точке пересечения.
		r_float u1 = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
		r_float u2 = seg2_line1_start / (seg2_line1_start - seg2_line1_end);
		*out_intersection =  start1 + u1 * dir1;

		//nos::println("result:", *out_intersection);
		return 1;
	}

	static inline
	int __intersect_points_segm2_polysegm2(
	    const segm2     * segm,
	    const polysegm2 * poly,
	    vec2 * points
	)
	{
		//vec2 points;//[poly.pnts_count];
		int results_count = 0;

		for (int i = 0; i < poly->pnts_count - 1; ++ i)
		{
			segm2 s(poly->pnts[i], poly->pnts[i + 1]);

			int finded = intersect_point_segm2_segm2(
			                  segm, &s, &points[results_count]);

			results_count += finded;
		}

		return results_count;
	}

	static inline
	int intersect_points_segm2_polysegm2(
	    const segm2     * segm,
	    const polysegm2 * poly,
	    vec2 * points,
	    r_float epsilon = r_epsilon
	)
	{
		int count = __intersect_points_segm2_polysegm2(
		                segm, poly, points);
		//PRINT(count);

		// Фильтруем точки на стыках отрезков.
		int count2 = 1;
		int write_it = 1;

		if (count == 0)
			return 0;

		for (int i = 1; i < count; ++i)
		{
			//PRINT(linalg::maxelem(points[i] - points[i - 1]) >= r_epsilon);
			if (i >= 1 && linalg::length0(points[i] - points[i - 1]) >= r_epsilon)
			{
				//nos::println("add point", write_it, i);
				points[write_it++] = points[i];
				count2++;
			}
		}

		/*PRINT(count2);
		PRINT(points[0]);
		PRINT(points[count2 - 1]);
		PRINT(linalg::maxelem(points[0] - points[count2 - 1]));*/
		if (count2 != 1 && linalg::length0(points[0] - points[count2 - 1]) < r_epsilon)
		{
			//nos::println("del last");
			count2--;
		}

		return count2;
	}

}

/*static inline
intersect_node intersect_segm2_segm2
(
    const rabbit::segm2& asegm,
    const rabbit::segm2& bsegm)
{
//	line2 alin = asegm.to_line();
//	line2 blin = bsegm.to_line();

//	intersect_node linlin = intersect_line2_line2(alin, blin);
}*/

#endif