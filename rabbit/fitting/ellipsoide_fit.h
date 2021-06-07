#ifndef RABBIT_ELLIPSOIDE_FITTING_H
#define RABBIT_ELLIPSOIDE_FITTING_H

#include <ralgo/linalg/svd.h>
#include <rabbit/types.h>
#include <ralgo/linalg/matrix.h>

namespace rabbit
{
	template <class Allocator>
	class ellipsoide_fit
	{
		ralgo::matrix_view_ro<real> data;
		ralgo::matrix<real, Allocator> _D;
		std::vector<vec3> _points;

	public:
		ellipsoide_fit(const std::vector<vec3> & points)
			:
			_points(points)
		{
			data = ralgo::matrix_view_ro<real>(&points[0], points.size(), 3);
			_D.resize(_points.size(), 9);
			init_D();
		}

		void init_D()
		{
			for (int i = 0; i < _D.rows(); ++i)
			{
				auto x = data.row(i)[0];
				auto y = data.row(i)[1];
				auto z = data.row(i)[2];

				auto x_sq = x * x;
				auto y_sq = y * y;
				auto z_sq = z * z;

				_D.at(i, 0) = x_sq + y_sq - 2. * z_sq;
				_D.at(i, 1) = x_sq + z_sq - 2. * y_sq;
				_D.at(i, 2) = 2. * x * y;
				_D.at(i, 3) = 2. * x * z;
				_D.at(i, 4) = 2. * y * z;
				_D.at(i, 5) = 2. * x;
				_D.at(i, 6) = 2. * y;
				_D.at(i, 7) = 2. * z;
				_D.at(i, 8) = 1;
			}
		}

		void solve()
		{
			//auto d2 = (x_sq + y_sq + z_sq).eval(); // the RHS of the llsq problem (y's)
			//auto u = (D.transpose() * D)
			//         .bdcSvd(Eigen::ComputeFullU | Eigen::ComputeFullV)
			//         .solve(D.transpose() * d2)
			//         .eval(); // solution to the normal equations
		}
	};
}

#endif