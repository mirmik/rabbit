#include <rabbit/intersect.h>
#include <igris/util/template_instance.h>

template <class T>
linalg::vec<T, 2> rabbit::intersect_point_line2_line2(
    const line2eq<T> & line1,
    const line2eq<T> & line2
)
{
	T a = line1.b * line2.c - line2.b * line1.c;
	T b = line2.a * line1.c - line1.a * line2.c;
	T c = line1.a * line2.b - line2.a * line1.b;

	return { a/c, b/c };
}


template <class T>
int rabbit::intersect_point_segm2_segm2(
    const segm2<T>   * segment1,
    const segm2<T>   * segment2,
    linalg::vec<T, 2> * out_intersection,
    T epsilon
)
{
	linalg::vec<T, 2> start1 = segment1->apnt;
	linalg::vec<T, 2> start2 = segment2->apnt;
	linalg::vec<T, 2> end1 = segment1->bpnt;
	linalg::vec<T, 2> end2 = segment2->bpnt;

	linalg::vec<T, 2> dir1 = end1 - start1;
	linalg::vec<T, 2> dir2 = end2 - start2;

	line2eq<T> eq1 = segment1->line_equation();
	line2eq<T> eq2 = segment2->line_equation();

	// подставляем концы отрезков, для выяснения в каких полуплоскотях они
	// точки первого отрезка подставляются во второе уравнение,
	// а второго в первое.
	T seg1_line2_start = eq2.subs(segment1->apnt);
	T seg1_line2_end = eq2.subs(segment1->bpnt);

	T seg2_line1_start = eq1.subs(segment2->apnt);
	T seg2_line1_end = eq1.subs(segment2->bpnt);

	// если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
	// Проверяем с учетом точности. Если отрезок подходит к другому ближе, чем на эпсилон, защитывается пересечение.
	if (seg1_line2_start * seg1_line2_end >= epsilon || seg2_line1_start * seg2_line1_end >= epsilon)
	{
		return 0;
	}

	// Из пропорции расстояний находим параметр в точке пересечения.
	T u1 = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
	T u2 = seg2_line1_start / (seg2_line1_start - seg2_line1_end);
	*out_intersection =  start1 + u1 * dir1;

	//nos::println("result:", *out_intersection);
	return 1;
}

template <class T>
int rabbit::__intersect_points_segm2_polysegm2(
    const segm2<T>     * segm,
    const polysegm2<T> * poly,
    linalg::vec<T, 2>   * points
)
{
	//linalg::vec<T,2> points;//[poly.pnts_count];
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

template <class T>
int rabbit::intersect_points_segm2_polysegm2(
    const segm2<T>     * segm,
    const polysegm2<T> * poly,
    linalg::vec<T, 2>   * points,
    T epsilon
)
{
	int count = __intersect_points_segm2_polysegm2(
	                segm, poly, points);

	// Фильтруем точки на стыках отрезков.
	int count2 = 1;
	int write_it = 1;

	if (count == 0)
		return 0;

	for (int i = 1; i < count; ++i)
	{
		if (i >= 1 && linalg::length0(points[i] - points[i - 1]) >= r_epsilon)
		{
			points[write_it++] = points[i];
			count2++;
		}
	}

	if (count2 != 1 && linalg::length0(points[0] - points[count2 - 1]) < r_epsilon)
	{
		count2--;
	}

	return count2;
}

TEMPLATE_INSTANCE(rabbit::intersect_point_segm2_segm2,float);
TEMPLATE_INSTANCE(rabbit::intersect_point_segm2_segm2,double);

TEMPLATE_INSTANCE(rabbit::intersect_points_segm2_polysegm2,float);
TEMPLATE_INSTANCE(rabbit::intersect_points_segm2_polysegm2,double);

TEMPLATE_INSTANCE(rabbit::intersect_point_line2_line2,float);
TEMPLATE_INSTANCE(rabbit::intersect_point_line2_line2,double);