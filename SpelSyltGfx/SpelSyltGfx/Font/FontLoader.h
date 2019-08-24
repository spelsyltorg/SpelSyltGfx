#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Font/Font.h"

#include <map>
#include <string>

namespace SSGFX
{
	class CFontLoader
	{
	public:
		CFontLoader();
		~CFontLoader();
		CFontLoader(const CFontLoader&) = delete;
		CFontLoader(CFontLoader&&) = delete;
		
		bool Initialize();

		void AddFont(const std::string& InPath);
		bool ContainsFont(const std::string& InFont) const;

		CFont& GetFont(const std::string& InPath);
		const CFont& GetFont(const std::string& InPath) const;
	private:
		FT_Library FreeTypeLibrary;
		std::map<std::string, CFont> FontFaceBank;
	};
}