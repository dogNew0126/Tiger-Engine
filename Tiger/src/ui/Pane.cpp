#include "Pane.h"

namespace tiger {
	namespace ui {

		Pane::Pane(const std::string& paneName, const glm::vec2& panePositon) : m_PaneName(paneName), m_PanePosition(panePositon) {
		}

		void Pane::render() {
			ImGui::SetNextWindowSize(ImVec2(m_PanePosition.x, m_PanePosition.y));
			ImGui::Begin(m_PaneName.c_str(), nullptr);
			setupPaneObjects();
			ImGui::End();
		}

	}
}