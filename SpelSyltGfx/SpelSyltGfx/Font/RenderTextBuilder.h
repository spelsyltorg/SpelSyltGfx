#pragma once
//#include <SpelSyltGFX/Font/Font.h>
#include <string>
#include <SpelSyltGfx/Rendering/VertexBuffer.h>
#include <SpelSyltGfx/Rendering/Bitmap.h>

namespace SSGFX
{
	class CFont;

	class CRenderTextBuilder
	{
	public:
		CRenderTextBuilder();
		CRenderTextBuilder(const CRenderTextBuilder& InOther);
		CRenderTextBuilder(const CFont& InFont);

		void SetFont(const CFont& InFont);
		void SetString(const std::string& InString);
		void Build();

		const SBitmap& GetBMP() const;
	private:
		const CFont* Font;
		std::string String;
		CVertexBuffer VertexBuffer;
		SBitmap BuiltBMP;
		SBitmap BuiltOutlineBMP;
	};
}
