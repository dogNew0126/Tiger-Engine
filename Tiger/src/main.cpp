#include "pch.h"

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/camera/FPSCamera.h"
#include "graphics/mesh/Model.h"
#include "graphics/mesh/common/Quad.h"
#include "graphics/renderer/GLCache.h"
#include "graphics/renderer/PostProcessor.h"
#include "platform/OpenGL/Framebuffers/RenderTarget.h"
#include "utils/Timer.h"
#include "utils/Time.h"
#include "utils/loaders/TextureLoader.h"
#include "terrain/Terrain.h"
#include "Scene3D.h"
#include "ui/RuntimePane.h"
#include "ui/DebugPane.h"

int main() {
	// Prepare the engine
	tiger::graphics::FPSCamera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	tiger::graphics::Window window("Tiger Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	tiger::Scene3D scene(&camera);
	tiger::graphics::GLCache* glCache = tiger::graphics::GLCache::getInstance();
	tiger::graphics::PostProcessor postProcessor(scene.getRenderer());

	tiger::utils::TextureLoader::initializeDefaultTextures();

	// Prepare the UI
	tiger::ui::RuntimePane runtimePane(glm::vec2(256.0f, 90.0f));
	tiger::ui::DebugPane debugPane(glm::vec2(256.0f, 100.0f));

	// Construct framebuffers
	bool shouldMultisample = MSAA_SAMPLE_AMOUNT > 1.0 ? true : false;
	tiger::opengl::RenderTarget framebuffer(window.getWidth(), window.getHeight());
	framebuffer.addColorAttachment(shouldMultisample).addDepthStencilRBO(shouldMultisample).createFramebuffer();

	tiger::opengl::RenderTarget shadowmap(SHADOWMAP_RESOLUTION_X, SHADOWMAP_RESOLUTION_Y);
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
		window.resetScroll();
		window.update();
	}

	return 0;
}
