#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_stdlib.h"

#include "ImguiPopup.hpp"

#include <bitset>

class ImguiRelationAddingPopup : public ImguiPopup
{
public:
	struct Form
	{
		bool name = true;
		bool weight = true;
		bool biderectional = true;
	};

	enum Type : uint8_t
	{
		Vertex = 0,
		Relation,
		VertexAndRelation
	};

	void open(Type type)
	{
		ImguiPopup::open();

		_name = std::to_string(_id);
		_type = type;

		if (type == Type::Vertex) {
			_form.name = true;
			_form.weight = false;
			_form.biderectional = false;
		}

		if (type == Type::Relation) {
			_form.name = false;
			_form.weight = true;
			_form.biderectional = true;
		}

		if (type == Type::VertexAndRelation) {
			_form.name = true;
			_form.weight = true;
			_form.biderectional = true;
		}
	}

	void render(void (*close_callback)(), void (*confirm_callback)(Type type, std::string name, std::string weight, bool biderectional))
	{
		if (_show) {
			ImGui::Begin("Vertex creating", &_show);

			if (!_show) {
				close_callback();
			}

			if (_form.name) {
				ImGui::InputText("Name", &_name);
			}

			if (_form.weight) {
				ImGui::InputText("Weight", &_weight);
			}

			if (_form.biderectional) {
				ImGui::Checkbox("Biderectional", &_biderectional);
			}

			if (ImGui::Button("Create"))
			{
				_id++;
				confirm_callback(_type, _name, _weight, _biderectional);
				close();
			}

			ImGui::SameLine();

			ImGui::End();
		}
	}

private:
	size_t _id = 0;
	std::string _weight = "1";
	std::string _name = "";
	bool _biderectional = false;

	Form _form;
	Type _type;
};
