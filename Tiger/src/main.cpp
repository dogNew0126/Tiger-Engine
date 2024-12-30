#include "pch.h"

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/camera/FPSCamera.h"
#include "graphics/mesh/Model.h"
#include "graphics/mesh/common/Quad.h"
#include "graphics/renderer/GLCache.h"
#include "graphics/renderer/PostProcessor.h"
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
	tiger::FPSCamera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	tiger::Window window("Tiger Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	tiger::Scene3D scene(&camera);
	tiger::GLCache* glCache = tiger::GLCache::getInstance();
	tiger::PostProcessor postProcessor(scene.getRenderer());

	tiger::TextureLoader::initializeDefaultTextures();

	// Prepare the UI
	tiger::RuntimePane runtimePane(glm::vec2(256.0f, 90.0f));
	tiger::DebugPane debugPane(glm::vec2(256.0f, 100.0f));

	// Construct framebuffers
	bool shouldMultisample = MSAA_SAMPLE_AMOUNT > 1.0 ? true : false;
	tiger::Framebuffer framebuffer(window.getWidth(), window.getHeight());
	framebuffer.addColorAttachment(shouldMultisample).addDepthStencilRBO(shouldMultisample).createFramebuffer();

	tiger::Framebuffer shadowmap(SHADOWMAP_RESOLUTION_X, SHADOWMAP_RESOLUTION_Y);
	shadowmap.addDepthAttachment(false).createFramebuffer();

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

		// Shadowmap Pass
#if DEBUG_ENABLED
		glFinish();
		timer.reset();
#endif
		glViewport(0, 0, shadowmap.getWidth(), shadowmap.getHeight());
		shadowmap.bind();
		shadowmap.clear();
		scene.shadowmapPass();
#if DEBUG_ENABLED
		glFinish();
		runtimePane.setShadowmapTimer(timer.elapsed());
#endif

		// Camera Update
		camera.processInput(deltaTime.getDeltaTime());

		// Draw the scene to our custom multisampled framebuffer
		glViewport(0, 0, framebuffer.getWidth(), framebuffer.getHeight());
		framebuffer.bind();
		framebuffer.clear();

		scene.onUpdate(deltaTime.getDeltaTime());
		scene.onRender(shadowmap.getDepthTexture());

		// Peform post processing
		postProcessor.postLightingPostProcess(&framebuffer);
		// Display panes
		runtimePane.render();
		debugPane.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	return 0;
}
