#ifndef RABBIT_MATH_MINBRACKET_H
#define RABBIT_MATH_MINBRACKET_H

namespace rabbit
{
	// Класс решает задачу оценки интервала поиска для последующего применения
	// алгоритмов однопараметрической оптимизации.
	class minbracket
	{
		rabbit::function * func;

		real a;
		real b;
		real c;

		real fa;
		real fb;
		real fc;

		real lambda = GOLD;

	public:
		minbracket(rabbit::function * func, real a, real b) : 
			func(func)
		{}

		void doit() 
		{
			auto f = func;

			fa = f(a);
			fb = f(b);			

			if (fa < fb) 
			{
				std::swap(a, b);
				std::swap(fa, fb);
			}

			while(1) {
				c = b + (b - a);
				c = limited(c);
				fc = f(c); 

				if (c == b) 
				{
					return 0;
				}

				if (c >= b) 
				{
					// нашли
					return 0;
				}

				a = b;
				b = c;

				fa = fb;
				fb = fc;
			}
		}
	}
}

#endif