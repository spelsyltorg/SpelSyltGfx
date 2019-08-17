#include "Texture.h"
#include "OpenGL.h"

SSGFX::CTexture::CTexture()
{
}

SSGFX::CTexture::~CTexture()
{
}

void SSGFX::CTexture::Create(const STextureDesc& Description)
{
	int amount = Description.Width * Description.Height * sizeof(char);
	char* pixels = new char[amount];
	for (int i = 0; i < amount; ++i)
	{
		pixels[0] = Description.FillColor.r * 255;
		pixels[1] = Description.FillColor.g * 255;
		pixels[2] = Description.FillColor.b * 255;
		pixels[3] = Description.FillColor.a * 255;
	}

	char p[4] = {0,255,0,255};

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, Description.Format, Description.Width, Description.Height, 0, Description.Format, GL_UNSIGNED_BYTE, pixels);

	delete pixels;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

int SSGFX::CTexture::GetID() const
{
	return ID;
}
