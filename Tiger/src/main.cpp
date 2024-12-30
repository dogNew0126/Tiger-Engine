#include "pch.h"

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/camera/FPSCamera.h"
#include "graphics/mesh/Model.h"
#include "graphics/mesh/common/Quad.h"
#include "graphics/renderer/GLCache.h"
#include "graphics/renderer/MasterRenderer.h"
#include "platform/OpenGL/Framebuffers/Framebuffer.h"
#include "utils/Timer.h"
#include "utils/Time.h"
#include "utils/loaders/TextureLoader.h"
#include "terrain/Terrain.h"
#include "scene/Scene3D.h"
#include "ui/RuntimePane.h"
#include "ui/DebugPane.h"
#include "input/InputManager.h"

int main() {
	// Prepare the engine
	tiger::Window window("Tiger Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	tiger::Scene3D scene(&window);
	tiger::MasterRenderer renderer(&scene);

	tiger::TextureLoader::initializeDefaultTextures();

	// Prepare the UI
	tiger::RuntimePane runtimePane(glm::vec2(256.0f, 90.0f));
	tiger::DebugPane debugPane(glm::vec2(256.0f, 100.0f));

#if DEBUG_ENABLED
	tiger::Timer timer;
#endif

	tiger::Time deltaTime;

	while (!window.closed()) {

		deltaTime.update();

#if DEBUG_ENABLED
		if (debugPane.getWireframeMode())
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

		window.clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		scene.onUpdate(deltaTime.getDeltaTime());
		renderer.render();

		// Display panes
		runtimePane.render();
		debugPane.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	return 0;
}
