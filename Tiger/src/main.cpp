#include "pch.h"

#include "graphics/Window.h"
#include "graphics/renderer/MasterRenderer.h"
#include "utils/Time.h"
#include "utils/loaders/TextureLoader.h"
#include "scene/Scene3D.h"
#include "ui/RuntimePane.h"
#include "ui/DebugPane.h"

int main() {
	// Prepare the engine
	tiger::Window window("Tiger Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	tiger::TextureLoader::initializeDefaultTextures();
	tiger::Scene3D scene(&window);
	tiger::MasterRenderer renderer(&scene);
	//tiger::InputManager manager;


	// Prepare the UI
	tiger::RuntimePane runtimePane(glm::vec2(270.0f, 175.0f));
	tiger::DebugPane debugPane(glm::vec2(270.0f, 400.0f));

	// Initialize the renderer
	renderer.init();

	tiger::Time deltaTime;

	while (!window.closed()) {

		deltaTime.update();

#if DEBUG_ENABLED
		if (debugPane.getWireframeMode())
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

		tiger::Window::bind();
		tiger::Window::clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//manager.update();

		scene.onUpdate(deltaTime.getDeltaTime());
		renderer.render();

		// Display panes
		tiger::Window::bind();
		runtimePane.render();
		debugPane.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	return 0;
}
