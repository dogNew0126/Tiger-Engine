#include <iostream>
#include "graphics/Window.h"
#include "utils/Timer.h"
#include "graphics/Shader.h"
#include <stb_image.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/Time.h"
#include "graphics/camera/Camera.h"
#include "utils/Logger.h"
#include "graphics/mesh/Model.h"
#include "terrain/Terrain.h"
#include "Scene3D.h"
#include "platform/OpenGL/Framebuffers/RenderTarget.h"
#include "graphics/mesh/common/Quad.h"
#include "graphics/renderer/GLCache.h"
#include "graphics/renderer/PostProcessor.h"
#include "ui/RuntimePane.h"
#include "ui/DebugPane.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype-gl.h>

int main() {
	// Prepare the engine
	tiger::graphics::Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	tiger::graphics::Window window("Tiger Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	tiger::Scene3D scene(&camera);
	tiger::graphics::GLCache* glCache = tiger::graphics::GLCache::getInstance();
	tiger::graphics::PostProcessor postProcessor(scene.getRenderer());

	tiger::utils::TextureLoader::initializeDefaultTextures();

	// Prepare the UI
	tiger::ui::RuntimePane runtimePane(glm::vec2(100.0f, 50.0f));
	tiger::ui::DebugPane debugPane(glm::vec2(100.0f, 150.0f));

	// Construct framebuffers
	tiger::opengl::RenderTarget framebuffer(window.getWidth(), window.getHeight());
	framebuffer.addColorAttachment(true).addDepthStencilRBO(true).createFramebuffer();

	// TODO: MAKE MULTISAMPLE OPTION WORK OR INVESTIGATE
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
