#pragma once
#include "GfxInclude.h"

namespace SSGFX
{
	class CTexture
	{
	public:

		struct STextureDesc
		{
			unsigned int Width;
			unsigned int Height;
			ETexFormat Format = RGBA;
			SColor FillColor;
		};

		CTexture();
		~CTexture();

		void Create(const STextureDesc& Description);
		int GetID() const;

	private:

		unsigned int ID = 0;
	};
}