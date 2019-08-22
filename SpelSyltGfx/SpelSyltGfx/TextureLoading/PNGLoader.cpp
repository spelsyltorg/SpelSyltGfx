#include "PNGLoader.h"

#include <libpng16/png.h>

#include <istream>
#include <iostream>

#ifdef _DEBUG
#pragma comment(lib, "libpng16_staticd")
#pragma comment(lib, "zlibstaticd")
#else
#pragma comment(lib, "libpng16_static")
#pragma comment(lib, "zlibstatic")
#endif

#define LOG(a) std::cout << a << std::endl;

SSGFX::PNGLoader::SPNGData SSGFX::PNGLoader::LoadPNG(const std::string & FileName)
{
	SPNGData data;
	png_structp pngPtr;
	png_infop infoPtr;
	png_byte colorType;
	png_byte bitDepth;
	png_bytep* rowPtr;

	char header[8];

	FILE* file;
	fopen_s(&file, FileName.c_str(), "rb");

	fread(header, 1, 8, file);
	if (png_sig_cmp((png_bytep)header, 0, 8))
		LOG("ERROR: " << FileName << " is not a .png file");

	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!pngPtr)
		LOG("Failed to read PNG struct of: " << FileName);

	infoPtr = png_create_info_struct(pngPtr);

	if (!pngPtr)
		LOG("Failed to read PNG struct info: " << FileName);

	if (setjmp(png_jmpbuf(pngPtr)))
		LOG("Failed during init_io: " << FileName);

	png_init_io(pngPtr, file);
	png_set_sig_bytes(pngPtr, 8);

	png_read_info(pngPtr, infoPtr);

	data.width = png_get_image_width(pngPtr, infoPtr);
	data.height = png_get_image_height(pngPtr, infoPtr);
	colorType = png_get_color_type(pngPtr, infoPtr);
	bitDepth = png_get_bit_depth(pngPtr, infoPtr);

	png_set_interlace_handling(pngPtr);
	png_read_update_info(pngPtr, infoPtr);

	if (setjmp(png_jmpbuf(pngPtr)))
		LOG("Failed to read image: " << FileName);

	rowPtr = (png_bytep*)malloc(sizeof(png_bytep) * data.height);
	for (int y = 0; y < data.height; ++y)
		rowPtr[y] = (png_byte*)malloc(png_get_rowbytes(pngPtr, infoPtr));

	png_read_image(pngPtr, rowPtr);

	fclose(file);

	int channels = 1;
	switch (colorType)
	{
	case PNG_COLOR_TYPE_RGBA:
		data.format = ETexFormat::RGBA;
		channels = 4;
		break;
	}

	int amount = data.width * data.height * channels;
	data.pixels = new char[amount];

	for (int y = 0; y < data.height; ++y)
	{
		png_byte* row = rowPtr[y];
		for (int x = 0; x < data.width; ++x)
		{
			png_byte* ptr = &(row[x*channels]);
			int index = channels * (x + y * data.width);
			data.pixels[index + 0] = ptr[0];
			data.pixels[index + 1] = ptr[1];
			data.pixels[index + 2] = ptr[2];
			data.pixels[index + 3] = ptr[3];
		}
	}
	
	delete rowPtr;

	return data;
}
