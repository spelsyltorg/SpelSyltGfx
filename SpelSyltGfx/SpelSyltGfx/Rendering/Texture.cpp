#include "Texture.h"
#include "OpenGL.h"
#include "TextureLoading/PNGLoader.h"
#include "Rendering/Bitmap.h"

SSGFX::CTexture::CTexture()
{
}

SSGFX::CTexture::~CTexture()
{
}

void SSGFX::CTexture::Create(const STextureDesc& Description)
{
	int channels;
	if (Description.Format == RGBA)
		channels = 4;
	else if (Description.Format == RGB)
		channels = 3;
	else if (Description.Format == RG)
		channels = 2;
	else if (Description.Format == RED || Description.Format == DEPTH)
		channels = 1;

	int amount = Description.Width * Description.Height * channels;
	char* pixels = new char[amount];
	for (int i = 0; i < amount/channels; ++i)
	{
		int p = channels * i;
		pixels[p+0] = Description.FillColor.r * 255;
		if (channels > 1)
			pixels[p+1] = Description.FillColor.g * 255;
		if (channels > 2)
			pixels[p+2] = Description.FillColor.b * 255;
		if (channels > 3)
			pixels[p+3] = Description.FillColor.a * 255;
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, Description.Format, Description.Width, Description.Height, 0, Description.Format, GL_UNSIGNED_BYTE, pixels);

	delete[] pixels;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void SSGFX::CTexture::Create(const SBitmap& InBitmap)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, InBitmap.GetWidth(), InBitmap.GetHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, InBitmap.GetData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void SSGFX::CTexture::Load(const std::string & FileName)
{
	auto data = PNGLoader::LoadPNG(FileName);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, data.format, data.width, data.height, 0, data.format, GL_UNSIGNED_BYTE, data.pixels);

	delete data.pixels;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

int SSGFX::CTexture::GetID() const
{
	return ID;
}
