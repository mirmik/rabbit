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
		struct correction_data 
		{
			std::vector<nd::point> points;
			std::vector<nd::vector> deltas;
		};

		static inline
		auto binary_hypercube_vertices(int dim)
		{
			std::vector<ralgo::vector<int>> vect;
			vect.resize(pow(2, dim));

			for (int i = 0; i < vect.size(); i++)
			{
				vect[i].resize(dim);
				int shift = 1;
				for (int j = 0; j < dim; j++)
				{
					auto val = !!(i & shift);
					shift <<= 1;
					vect[i][dim - j - 1] = val;
				}
			}

			return vect;
		}

		// Вернуть коэфициенты точек, из которых нужно извлекать
		// значения для коррекции в правильном порядке.
		static inline
		auto multidim_cell_indices(ralgo::vector<int> indices)
		{
			std::vector<ralgo::vector<int>> ret = binary_hypercube_vertices(indices.size());
			for (auto& r : ret)
			{
				r += indices;
			}
			return ret;
		}


		class cartesian_cell
		{
		public:
			ralgo::vector<double> mins;
			ralgo::vector<double> maxs;

		public:
			cartesian_cell(
			    ralgo::vector<double> mins,
			    ralgo::vector<double> maxs
			) : mins(mins), maxs(maxs)
			{}

			ralgo::vector<double> lerpcoeffs(nd::point const & pnt)
			{
				ralgo::vector<double> coeffs(pnt.size());
				for (int i = 0; i < pnt.size(); i++)
				{
					coeffs[i] = ralgo::lerpcoeff(mins[i], maxs[i], pnt[i]);
				}
				return coeffs;
			}
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

			cartesian_sliced_zone()
			{}

			void set_zone(const std::vector<std::vector<double>>& zone)
			{
				this->coords = zone;
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

			auto point_in_cell_indices(nd::point point)
			{
				ralgo::vector<int> indexes(dim());

				for (size_t i = 0; i < coords.size(); ++i)
				{
					double minc = *coords[i].begin();
					double maxc = *coords[i].rbegin();

					if (point[i] < minc || point[i] > maxc)
					{
						//not in zone
						throw std::logic_error("not in zone");
					}

					auto git = std::lower_bound(coords[i].begin(), coords[i].end(), point[i]);
					auto lit = std::next(git, -1);

					indexes[i] = std::distance(coords[i].begin(), lit);
				}

				return indexes;
			}

			cartesian_cell cellzone(ralgo::vector<int> indexes)
			{
				ralgo::vector<double> mins(indexes.size());
				ralgo::vector<double> maxs(indexes.size());

				for (int i = 0; i < dim(); ++i)
				{
					mins[i] = coords[i][indexes[i]];
					maxs[i] = coords[i][indexes[i] + 1];
				}

				return { mins, maxs };
			}
		};

		class deltacloud
		{
			igris::ndarray<nd::vector> _deltas;
			cartesian_sliced_zone _grid;

		public:
			cartesian_sliced_zone& grid() { return _grid; }
			igris::ndarray<nd::vector>& deltas() { return _deltas; }

			size_t dim() const { return _grid.dim(); }

			deltacloud() {}

			deltacloud(std::vector<std::vector<double>> gridcoords)
				: _grid(gridcoords) {}

			void set_deltas(igris::ndarray<nd::vector> deltas)
			{
				_deltas = deltas;

				if (deltas[0].size() != dim()) 
					throw std::runtime_error("deltas has no same dim as deltacloud");
			}

			nd::vector apply_lerpcoeffs(
				ralgo::vector<double> coeffs,
				std::vector<ralgo::vector<double>> celldeltas
			) 
			{
				nd::vector ret(coeffs.size());
				auto cube = binary_hypercube_vertices(coeffs.size());
				assert(cube.size() == celldeltas.size());
				assert(coeffs.size() == cube[0].size());
				for (int v = 0; v < cube.size(); ++v)
				{
					double mul = 1;
					for (int i = 0; i < cube[v].size(); ++i) 
					{
						mul *= cube[v][i] ? coeffs[i] : 1-coeffs[i];
					}
					ret += celldeltas[v] * mul;
				}
				return ret;
			}

			correction_data delta_correction(
			    const rabbit::nd::segment& segm,
			    size_t npoints
			)
			{
				//rabbit::nd::polysegment polysegm;
				std::vector<rabbit::nd::point> points;
				std::vector<rabbit::nd::vector> deltas;
				auto uniform =
				    ralgo::linspace(segm.apnt, segm.bpnt, npoints);

				for (const auto& pnt : uniform)
				{
					ralgo::vector<int> cellzone_indices = _grid.point_in_cell_indices(pnt);
					std::vector<ralgo::vector<int> >ndarray_indices = multidim_cell_indices(cellzone_indices);
					cartesian_cell cellzone = _grid.cellzone(cellzone_indices);
					ralgo::vector<double> coeffs = cellzone.lerpcoeffs(pnt);
					auto celldeltas = _deltas.get(ndarray_indices);

					nd::vector correction = apply_lerpcoeffs(coeffs, celldeltas);
					deltas.push_back(correction);
					points.push_back(pnt);
				}

				return  { points, deltas };
			}

			void set_zone(const std::vector<std::vector<double>>& zone)
			{
				_grid.set_zone(zone);
			}
		};
	}
}

#endif