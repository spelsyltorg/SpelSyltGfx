#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H

#include <string>
#include <SpelSyltGFX/Rendering/Bitmap.h>

#define ASCII_MAX 0xFF

namespace SSGFX
{
	struct SGlyph
	{
		SGlyph()
			: BearingX(0)
			, BearingY(0)
			, Advance(0)
			, BMPRep()
		{
		}

		SGlyph(const SGlyph&) = delete;

		unsigned int BearingX, BearingY;
		unsigned int Advance;
		SBitmap BMPRep;
	};

	class CFont
	{
	public:
		CFont();
		CFont(const CFont& InFont);
		bool Load(FT_Library& InLoaderLibrary, const std::string& InPath);
		void SetFontSize(unsigned int InSize);

		const SGlyph& GetGlyph(char InASCIIChar) const;

		CFont& operator=(const CFont& InRHS);
	private:
		FT_Face FontFace;
		SGlyph GlyphCache[ASCII_MAX];
		unsigned int FontSize;
	};
}