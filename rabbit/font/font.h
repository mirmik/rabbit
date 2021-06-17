#ifndef RABBIT_FONT_H
#define RABBIT_FONT_H

namespace rabbit 
{
	using font_producer_t = opengl_texture(*)(int code);

	class font 
	{
	public:
		opengl_texture textures[256];
		
		font(font_producer_t producer) 
		{
			for (int i = 0; i < 256; ++i) 
			{
				textures[i] = producer(i);
				textures[i].bind();
			}
		}

		opengl_texture & operator[] (int code) 
		{
			return textures[code];
		}
	};
}

#endif