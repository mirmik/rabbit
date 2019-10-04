#ifndef igris_NGEOM_H
#define igris_NGEOM_H

//#include <igris/array.h>
#include <igris/objbuf.h>
#include <malgo/oldfunc.h>

#include <limits>

namespace rabbit { 
	namespace ngeom {

		constexpr static double infinity = std::numeric_limits<double>::infinity();
		constexpr static double E = 0.00000001;

		class coordinates : public oldmalgo::vector<double> {
		public:
			coordinates(size_t size) : oldmalgo::vector<double>(size) {}
			coordinates(igris::objbuf<double> buf) : oldmalgo::vector<double>(buf) {}	
			coordinates(const std::initializer_list<double>& buf) : oldmalgo::vector<double>(buf) {}	
			coordinates(const coordinates&) = default; 
			coordinates(coordinates&&) = default; 
			size_t dim() const { return size(); }
		};

		class point : public coordinates  {
		public:
			point(size_t sz) : coordinates(sz) {}
			point(const igris::objbuf<double>& buf) : coordinates(buf) {}
			point(const std::initializer_list<double>& lst) : coordinates(lst) {}
			point(const point& oth) = default;
			point(point&& oth) = default;
		};

		class direction : public coordinates {
		public:
			direction(igris::objbuf<double> buf) : coordinates(buf) {
				self_normalize();
			}			
		};

		inline point linear_interpolation_2point(const point& a, const point& b, double k) {
			size_t dim = a.dim();
			double tmp[dim];
			point c(dim);
			
			auto A = a.data();
			auto B = b.data();
			auto C = c.data();

			oldmalgo::vector_scale(A, dim, 1 - k, tmp);
			oldmalgo::vector_scale(B, dim, k, C);
			oldmalgo::vector_add(tmp, C, dim, C);
			return c;
		}
	}
}
#endif