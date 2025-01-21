#include "ImguiVertexAddingPopup.h"



void ImguiVertexAddingPopup::open()
{
	_show = true;
	_name = std::to_string(_id);
}

void ImguiVertexAddingPopup::close()
{
	_show = false;
}

void ImguiVertexAddingPopup::render(bool with_edge, void(*close_callback)(), void(*confirm_callback)(std::string name, std::string weight, bool biderectional))
{
	if (_show) {
		ImGui::Begin("Vertex creating", &_show);

		if (!_show) {
			close_callback();
		}

		ImGui::InputText("Name", &_name);

		if (with_edge) {
			ImGui::InputText("Weight", &_weight);
			ImGui::Checkbox("Biderectional", &_biderectional);
		}

		if (ImGui::Button("Create"))
		{
			_id++;
			confirm_callback(_name, _weight, _biderectional);
			close();
		}

		ImGui::SameLine();

		ImGui::End();
	}
}

bool ImguiVertexAddingPopup::opened()
{
	return _show;
}
