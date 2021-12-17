#ifndef RABBIT_DELTAZONE_H
#define RABBIT_DELTAZONE_H

#include <igris/container/ndarray.h>
#include <igris/util/ab_converter.h>
#include <ralgo/linalg/vector.h>
#include <ralgo/linspace.h>
#include <ralgo/linalg/vecops.h>
#include <rabbit/nd/point.h>
#include <rabbit/nd/segment.h>
#include <rabbit/nd/polysegment.h>
#include <rabbit/nd/cartesian_correction.h>

namespace rabbit
{
	namespace nd
	{
		class correction_data
		{
			std::vector<nd::point> _points;
			std::vector<nd::vector> _deltas;

		public:
			correction_data(
			    const std::vector<nd::point>& pnts,
			    const std::vector<nd::vector>& dlts
			)
				: _points(pnts), _deltas(dlts)
			{}

			std::vector<nd::point> points() { return _points; }
			std::vector<nd::vector> deltas() { return _deltas; }


			nd::polysegment compile_polysegment()
			{
				nd::polysegment ret;
				for (size_t i = 0; i < _points.size(); ++i)
					ret.add_point(_points[i] + _deltas[i]);
				return ret;
			}
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

		class cartesian_correction
		{
			igris::ndarray<nd::vector> _deltas;
			cartesian_sliced_zone _grid;
			std::vector<int> grid_index_converter;

			int fulldim;
			// Слева координаты дельта пространства, справа - полного пространства.
			igris::ab_converter<int, int> delta2full_converter;
			// Слева координаты пространства сетки, справа - полного пространства.
			igris::ab_converter<int, int> grid2full_converter;

		public:
			cartesian_sliced_zone& grid() { return _grid; }
			igris::ndarray<nd::vector>& deltas() { return _deltas; }

			void set_fulldim(int fulldim) 
			{
				this->fulldim = fulldim;
			}

			void set_delta_to_full_indexes(igris::ab_converter<int, int> converter)
			{
				this->delta2full_converter = converter;
			}

			void set_grid_to_full_indexes(igris::ab_converter<int, int> converter)
			{
				this->grid2full_converter = converter;
			}

			size_t griddim() const { return _grid.dim(); }

			// Приводит дельта вектор приведенный к полному виду.
			ralgo::vector<double> fulled_delta(const ralgo::vector<double>& delta)
			{
				ralgo::vector<double> full(fulldim);
				ralgo::vecops::fill(full, 0);
				for (int i = 0; i < _deltas.dim(); ++i)
				{
					full[delta2full_converter.b(i)] = delta[i];
				}
				return full;
			}

			// Возвращает вектор координат представляющий точку
			// в системе координат сетки.
			ralgo::vector<double> zoned_point(const ralgo::vector<double>& point)
			{
				ralgo::vector<double> vec(griddim());
				ralgo::vecops::fill(vec, 0);
				for (int i = 0; i < _grid.dim(); ++i)
				{
					vec[i] = point[grid2full_converter.b(i)];
				}
				return vec;
			}

			size_t dim() const { return _grid.dim(); }

			cartesian_correction() {}

			cartesian_correction(std::vector<std::vector<double>> gridcoords)
				: _grid(gridcoords) {}

			void set_deltas(const igris::ndarray<nd::vector>& deltas)
			{
				_deltas = deltas;

				/*if (deltas[0].size() != dim())
					throw std::runtime_error("deltas has no same dim as cartesian_correction");
				*/
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
						mul *= cube[v][i] ? coeffs[i] : 1 - coeffs[i];
					}
					ret += celldeltas[v] * mul;
				}
				return ret;
			}

			auto corrected_point(const nd::vector& pnt)
			{
				assert(pnt.size() == fulldim);

				auto gridpnt = zoned_point(pnt);
				auto cellzone_index = _grid.point_in_cell_indices(gridpnt);
				auto cellzone = _grid.cellzone(cellzone_index);
				auto deltas_indices = multidim_cell_indices(cellzone_index);
				auto coeffs = cellzone.lerpcoeffs(gridpnt);
				auto celldeltas = _deltas.get(deltas_indices);
				auto pnt_delta = apply_lerpcoeffs(coeffs, celldeltas);

				return pnt + fulled_delta(pnt_delta);
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