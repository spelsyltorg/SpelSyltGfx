#pragma once
#include <string>
#include "SpelSyltGfx/Rendering/GfxInclude.h"

namespace SSGFX
{
	namespace PNGLoader
	{
		struct SPNGData
		{
			size_t width;
			size_t height;
			ETexFormat format;
			char* pixels;
		};

		SSGFX::PNGLoader::SPNGData LoadPNG(const std::string& FileName);
	}
}