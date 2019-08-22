#pragma once
#include "GfxInclude.h"
#include <string>

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
		void Load(const std::string& FileName);
		int GetID() const;

	private:

		unsigned int ID = 0;
	};
}