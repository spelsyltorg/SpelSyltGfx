#include "Font/FontLoader.h"

#include FT_ERRORS_H

//----------------------------------------------------------------

SSGFX::CFontLoader::CFontLoader()
	: FreeTypeLibrary(nullptr)
	, FontFaceBank()
{
}

//----------------------------------------------------------------

SSGFX::CFontLoader::~CFontLoader()
{
	if (FreeTypeLibrary)
	{
		FT_Done_FreeType(FreeTypeLibrary);
	}
}

//----------------------------------------------------------------

bool SSGFX::CFontLoader::Initialize()
{
	if (FT_Init_FreeType(&FreeTypeLibrary) != FT_Err_Ok)
	{
		return false;
	}
}

//----------------------------------------------------------------

void SSGFX::CFontLoader::AddFont(const std::string& InPath)
{
	if (ContainsFont(InPath))
	{
		return;
	}

	FontFaceBank[InPath].Load(FreeTypeLibrary, InPath);
}

//----------------------------------------------------------------

bool SSGFX::CFontLoader::ContainsFont(const std::string& InFont) const
{
	return (FontFaceBank.find(InFont) != FontFaceBank.end());
}

//----------------------------------------------------------------

SSGFX::CFont& SSGFX::CFontLoader::GetFont(const std::string& InPath)
{
	AddFont(InPath);
	return FontFaceBank[InPath];
}

//----------------------------------------------------------------

const SSGFX::CFont& SSGFX::CFontLoader::GetFont(const std::string& InPath) const
{
	return FontFaceBank.at(InPath);
}

//----------------------------------------------------------------