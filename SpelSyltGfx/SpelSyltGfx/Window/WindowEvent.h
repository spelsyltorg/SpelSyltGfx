#pragma once
namespace SSGFX
{
	enum class EEventType
	{
		RESIZE
	};

	struct SWindowEvent
	{
		EEventType type;
		int x;
		int y;
	};
}