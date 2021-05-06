#ifndef RABBIT_MATH_OPTIMIZE_H
#define RABBIT_MATH_OPTIMIZE_H

namespace rabbit 
{
	using minimized_function_t = real(*)(real *);


	class optimization 
	{
	public:
		minimized_function_t minimized_function;

		real * minbound;
		real * maxbound;

		uint8_t dim;

	public:
		optimization(
			minimized_function_t minimized_function,
			real * minbound,
			real * maxbound,
			uint8_t dim
		)
		:
			minimized_function(minimized_function),
			minbound(minbound),
			maxbound(maxbound),
			dim(dim) 
		{}

		void compute_cell_minimum(real cellsize, real * out, real * result) 
		{
			real tmp[dim];
			compute_cell_minimum_recurse(cellsize, 0, tmp, out, result);
		}

	private:
		void compute_cell_minimum_recurse(
			real cellsize, 
			int j, 
			real * curval,
			real * out, 
			real * result
		) 
		{
			curval[j] = minbound[j];

			while(curval[j] <= maxbound[j]) 
			{
				if (j == dim - 1) 
				{
					real value = minimized_function(curval);

					if (value < *result) 
					{
						*result = value;
						memcpy(out, curval, sizeof(real) * dim);
					}
				}
				
				else 
				{
					compute_cell_minimum_recurse(
						cellsize, j + 1, curval, out, result);
				}

				curval[j] += cellsize;
			}
		}
	}
}

#endif