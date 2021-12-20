#ifndef NAMED_CARTESIAN_CORRECTION_H
#define NAMED_CARTESIAN_CORRECTION_H

#include <rabbit/nd/cartesian_correction.h>
#include <igris/util/ab_converter.h>
#include <igris/trent/trent.h>

namespace rabbit
{
	namespace nd
	{
		static auto make_numeric_index_converter(
		    const std::vector<std::string>& fullset,
		    const std::vector<std::string>& partset
		)
		{
			igris::ab_converter<int, int> ret;
			for (int i = 0; i < partset.size(); ++i)
			{
				auto it = std::find(
				              fullset.begin(),
				              fullset.end(),
				              partset[i]);

				if (it == fullset.end())
					throw std::runtime_error("bad partset index");

				ret.add(i, std::distance(fullset.begin(), it));
			}
			return ret;
		}

		struct named_correction_table
		{
			std::vector<std::string> head_full;
			std::vector<std::string> head_grid;
			std::vector<std::string> head_deltas;
			std::vector<std::vector<double>> grid;
			igris::ndarray<nd::vector> deltas;
		};

		static inline
		auto foo(const igris::trent& tr, auto it)
		{
			if (tr[0].is_numer())
			{
				nd::vector vec;
				for(auto & t : tr.as_list())
					vec.push_back(t.as_numer());
				*it = vec;
				return ++it;
			}
			else
			{
				for (const auto& t : tr.as_list())
					it = foo(t, it);
				return it;
			}
		}


		static struct named_correction_table
		parse_correction_table(const igris::trent& tr)
		{
			std::vector<std::string> head_full;
			std::vector<std::string> head_grid;
			std::vector<std::string> head_deltas;
			std::vector<std::vector<double>> grid;
			igris::ndarray<nd::vector> deltas;

			for (const auto& t : tr["head"]["full"].as_list())
				head_full.push_back(t.as_string());

			for (const auto& t : tr["head"]["grid"].as_list())
				head_grid.push_back(t.as_string());

			for (const auto& t : tr["head"]["deltas"].as_list())
				head_deltas.push_back(t.as_string());

			{
				int i = 0;
				grid.resize(tr["grid"].as_list().size());
				for (const auto& t : tr["grid"].as_list())
				{
					for (const auto& d : t.as_list())
					{
						assert(d.is_numer());
						grid[i].push_back(d.as_numer());
					}
					i++;
				}
			}

			{
				int grid_dimension = head_grid.size();
				std::vector<size_t> shape(grid_dimension);

				const igris::trent * it = &tr["deltas"];
				for (int i = 0; i < grid_dimension; i++)
				{
					shape[i] = it->as_list().size();
					it = &(*it)[0];
				}

				deltas.resize(shape);
				foo(tr["deltas"], deltas.begin());
			}

			return { head_full, head_grid, head_deltas, grid, deltas };
		}
	}
}

#endif