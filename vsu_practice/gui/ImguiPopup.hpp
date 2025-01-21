#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_stdlib.h"

class ImguiPopup
{
public:
	void open()
	{
		_show = true;
	}

	void close()
	{
		_show = false;
	}

	bool opened()
	{
		return _show;
	}

protected:
	bool _show = false;
};
