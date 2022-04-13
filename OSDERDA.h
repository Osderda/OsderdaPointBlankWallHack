
#include <stdint.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include "Imgui/imgui.h"

bool m_iDirectX = true;
bool m_iVisualEsp = false;
bool GlowEsp = false;
bool dwWallhack = false;

namespace OSDERDA {

	namespace UI {
		inline void DisabledInput() {
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}

		inline void EndDisabledInput() {
			ImGui::PopStyleVar();
		}
		inline void SeparatorWithPadding(ImVec2 padding) {
			ImGui::Dummy(padding);
			ImGui::Separator();
			ImGui::Dummy(padding);
		}
		inline void VisualEsp() {;
			ImGui::Checkbox("+ Wallhack", &dwWallhack);
		}
	}
}