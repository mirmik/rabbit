#ifndef NAMED_CARTESIAN_CORRECTION_H
#define NAMED_CARTESIAN_CORRECTION_H

#include <rabbit/nd/cartesian_correction.h>

namespace rabbit 
{
	class named_cartesian_correction 
	{
		cartesian_correction raw_correction;

		std::vector<std::string> _full_form_names;	
		std::vector<std::string> _zone_axes_names;
		std::vector<std::string> _deltas_axes_names;

		igris::ab_converter<std::string, int> full2idx_converter;
		igris::ab_converter<std::string, int> zone2idx_converter;
		igris::ab_converter<std::string, int> delta2idx_converter;

	public:
		named_cartesian_correction() = default;

		void set_full_axes_names(std::vector<std::string>& names)
		{
			_full_form_names = names;
			for (int i = 0; i < names.size(); ++i) 
			{
				full2idx_converter(names[i], i);
			}
		}

		size_t zone_dimension() const { return _zone_axes_names.size(); }
		size_t deltas_dimension() const { return _deltas_axes_names.size(); }
		size_t output_dimension() const { return _output_axes_names.size(); }

		void set_zone_names(const std::vector<std::string>& zone_axes_names) 
		{
			this->_zone_axes_names = zone_axes_names;
		}

		void set_deltas_names(const std::vector<std::string>& deltas_axes_names) 
		{
			this->_deltas_axes_names = deltas_axes_names;
		}

		std::vector<std::string>& output_axes_names() 
		{
			return _output_axes_names;;
		}

		void parse(const igris::trent& tr);
	};
}

#endif