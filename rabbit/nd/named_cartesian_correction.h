#ifndef NAMED_CARTESIAN_CORRECTION_H
#define NAMED_CARTESIAN_CORRECTION_H

#include <rabbit/nd/cartesian_correction.h>
#include <igris/util/ab_converter.h>

namespace rabbit
{
	namespace nd
	{
		static auto make_numeric_index_converter(
			const std::vector<std::string>& fullset, 
			const std::vector<std::string>& partset 
		) 
		{
			igris::ab_converter<int,int> ret;
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

	}
}

#endif