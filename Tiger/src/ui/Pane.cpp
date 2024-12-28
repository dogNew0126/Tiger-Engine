#include "pch.h"
#include "Pane.h"

namespace tiger {
	namespace ui {

		Pane::Pane(const std::string& paneName, const glm::vec2& paneSize) : m_PaneName(paneName), m_PaneSize(paneSize) {
		}

		void Pane::render() {
			ImGui::SetNextWindowSize(ImVec2(m_PaneSize.x, m_PaneSize.y));
			ImGui::Begin(m_PaneName.c_str(), nullptr);
			setupPaneObjects();
			ImGui::End();
		}

	}
}