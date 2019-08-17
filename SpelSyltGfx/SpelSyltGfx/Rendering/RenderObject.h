#pragma once

namespace SSGFX
{
	class CRenderObject
	{
	public:
		CRenderObject();
		~CRenderObject();

		void Bind();

	private:
		unsigned int ID;
	};
}