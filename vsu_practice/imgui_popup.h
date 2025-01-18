#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_stdlib.h"

class ImguiPopup
{
public:
	void open();
	void close();
	void render(bool with_edge, void (*close_callback)(), void (*confirm_callback)(std::string name, std::string weight, bool biderectional));

	bool opened();

private:
	bool _show = false;
	size_t _id = 0;
	std::string _weight = "1";
	std::string _name = "";
	bool _biderectional = false;
};
