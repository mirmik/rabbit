#ifndef RABBIT_TEXTZONE_H
#define RABBIT_TEXTZONE_H

namespace rabbit
{
	class textzone
	{
		int width;
		int heignt;

		linalg::vec<float, 3> lt = {0, 1, 0};
		linalg::vec<float, 3> rt = {1, 1, 0};
		linalg::vec<float, 3> lb = {0, 0, 0};
		linalg::vec<float, 3> rb = {1, 0, 0};

		void bind_coords(
		    linalg::vec<float, 3> lt,
		    linalg::vec<float, 3> rt,
		    linalg::vec<float, 3> lb,
		    linalg::vec<float, 3> rb) 
		{
			this->lt = lt;
			this->rt = rt;
			this->lb = lb;
			this->rb = rb;
		}

		void zone_for_cell(
			int row, 
			int column,
		    linalg::vec<float, 3> & _lt,
		    linalg::vec<float, 3> & _rt,
		    linalg::vec<float, 3> & _lb,
		    linalg::vec<float, 3> & _rb) 
		{
			float rkoeff1 = (float)row / (float)(height);  
			float сkoeff1 = (float)column / (float)(width);
			float rkoeff2 = (float)(row+1) / (float)(height);  
			float сkoeff2 = (float)(column+1) / (float)(width);
			
			_lt = ralgo::bilinear_interpolation(rkoeff1, ckoeff1, lt, rt, lb, rb);
			_rt = ralgo::bilinear_interpolation(rkoeff1, ckoeff2, lt, rt, lb, rb);
			_lb = ralgo::bilinear_interpolation(rkoeff2, ckoeff1, lt, rt, lb, rb);
			_rb = ralgo::bilinear_interpolation(rkoeff2, ckoeff2, lt, rt, lb, rb);
		}
	};
}

#endif