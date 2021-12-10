#ifndef RABBIT_DELTAZONE_H
#define RABBIT_DELTAZONE_H

#include <igris/container/ndarray.h>
#include <ralgo/linalg/vector.h>
#include <ralgo/linspace.h>
#include <rabbit/nd/point.h>
#include <rabbit/nd/segment.h>
#include <rabbit/nd/polysegment.h>

namespace rabbit
{
	namespace nd
	{

		// Вернуть коэфициенты точек, из которых нужно извлекать
		// значения для коррекции в правильном порядке.
		static inline 
		std::vector<std::vector<int>> multidim_cell_indices(std::vector<int> indices)
		{
			std::vector <std::vector<int>> wided;
			int dim = indices.size();

			wided.resize(pow(2, dim));

			for (int i = 0; i < indices.size(); i++)
			{
				wided[i].resize(dim);
				int shift = 1;
				for (int j = 0; j < dim; j++)
				{
					auto val = i & shift;
					shift <<= 1;
					wided[i][j] = val;
				}
			}

			return wided;
		}


		class cartesian_space_cell
		{
			std::vector<double> min;
			std::vector<double> max;
		};

		class cartesian_sliced_zone
		{
			std::vector<std::vector<double>> coords;
			std::vector<int> collapsed_dims;

		public:
			cartesian_sliced_zone(std::vector<std::vector<double>> coords) 
				: coords(coords)
			{

			}

			// определяет принадлежность к измерению,
			// сетка по которому не построена.
			bool is_collapsed_dim(int i)
			{
				return std::find(collapsed_dims.begin(), collapsed_dims.end(), i) 
					!= collapsed_dims.end();
			}

			// определяет измерению
			// находится ли точка в границах зоны
			// по одному из измерений.
			bool in_dim_interval()
			{
				return false;
			}

			size_t dim() const { return coords.size(); }

			std::vector<int> point_in_cell_indices(nd::point point)
			{
				for (int i = 0; i < dim(); ++i)
				{
					if (is_collapsed_dim(i))
					{

					}

					//
				}

				throw std::runtime_error("not in zone");


				std::vector<int> indexes;

			}
		};

		class deltacloud
		{
			int dim;
			igris::ndarray<nd::vector> deltas;
			cartesian_sliced_zone grid;

		public:
			deltacloud(std::vector<std::vector<double>> gridcoords)
				: grid(gridcoords) {}

			rabbit::nd::polysegment delta_correction(
			    const rabbit::nd::segment& segm,
			    double step
			)
			{
				rabbit::nd::polysegment polysegm;

				auto uniform =
				    ralgo::linspace(segm.apnt, segm.bpnt, segm.length() / step);

				for (auto& pnt : uniform)
				{
					std::vector<int> cellzone_indices = grid.point_in_cell_indices(pnt);
					std::vector<int> ndarray_indices = multidim_cell_indices(cellzone_indices);

					std::vector<std::pair<double, double>> cellzone = grid.cellzone(cellzone_indices);

					std:: nd::linear_interpolation_coefficients(pnt, cellzone);


					polysegm.push_back(pnt + correction);
				}
			}
		};
	}
}

#endif