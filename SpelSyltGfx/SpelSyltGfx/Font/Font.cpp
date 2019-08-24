#include "Font/Font.h"
#include "Rendering/Bitmap.h"

//----------------------------------------------------------------

SSGFX::CFont::CFont()
	: FontFace(nullptr)
	, FontSize(16)
{
}

//----------------------------------------------------------------

SSGFX::CFont::CFont(const CFont& InFont)
	: FontFace(nullptr)
	, FontSize(16)
{
	operator=(InFont);
}

//----------------------------------------------------------------

bool SSGFX::CFont::Load(FT_Library& InLoaderLibrary, const std::string& InPath)
{
	if (FT_New_Face(InLoaderLibrary, InPath.c_str(), 0, &FontFace) != FT_Err_Ok)
	{
		return false;
	}

	//Ensure we always have at least a small version loaded
	SetFontSize(FontSize);

	return true;
}

//----------------------------------------------------------------

void SSGFX::CFont::SetFontSize(unsigned int InSize)
{
	FontSize = InSize;
	FT_Set_Pixel_Sizes(FontFace, 0, FontSize);

	//Cache all current size bmps
	for (unsigned short i = 0; i < ASCII_MAX; ++i)
	{
		SGlyph& Glyph = GlyphCache[i];

		FT_Load_Char(FontFace, i, FT_LOAD_RENDER);
		auto FreeTypeGlyph = FontFace->glyph;
		auto CharBMP = FreeTypeGlyph->bitmap;

		Glyph.Advance = FreeTypeGlyph->advance.x / 64;
		Glyph.BearingX = static_cast<unsigned int>(FreeTypeGlyph->bitmap_left);
		Glyph.BearingY = static_cast<unsigned int>(FreeTypeGlyph->bitmap_top);

		Glyph.BMPRep.SetSize(CharBMP.width, CharBMP.rows);
		Glyph.BMPRep.SetData(CharBMP.buffer, CharBMP.width * CharBMP.rows);
	}
}

//----------------------------------------------------------------

SSGFX::CFont& SSGFX::CFont::operator=(const CFont& InRHS)
{
	FontFace = InRHS.FontFace;
	FontSize = InRHS.FontSize;
	SetFontSize(FontSize);

	return *this;
}

//----------------------------------------------------------------

const SSGFX::SGlyph& SSGFX::CFont::GetGlyph(char InASCIIChar) const
{
	return GlyphCache[InASCIIChar];
}

//----------------------------------------------------------------