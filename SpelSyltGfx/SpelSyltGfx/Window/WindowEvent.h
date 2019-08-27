#pragma once
namespace SSGFX
{
	enum class EEventType
	{
		QUIT,
		RESIZE,

		KEY_DOWN,
		KEY_RELEASED,
		MOUSE_POS,
		MOUSE_SCROLL,
	};

	struct SWindowEvent
	{
		EEventType type;
		int x;
		int y;
		int value;
	};
}