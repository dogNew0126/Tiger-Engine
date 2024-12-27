#pragma once

#include "graphics/renderer/Renderable3D.h"
#include "graphics/camera/FPSCamera.h"
#include "graphics/renderer/MeshRenderer.h"
#include "graphics/renderer/GLCache.h"
#include "terrain/Terrain.h"
#include "graphics/Window.h"
#include "graphics/Skybox.h"
#include "graphics/dynamic_lights/DynamicLightManager.h"
#include "utils/loaders/TextureLoader.h"
#include "Defs.h"

namespace tiger {

	class Scene3D {

	private:
		graphics::FPSCamera* m_Camera;
		graphics::MeshRenderer* m_Renderer;
		terrain::Terrain* m_Terrain;
		graphics::Skybox* m_Skybox;
		graphics::DynamicLightManager m_DynamicLightManager;
		graphics::GLCache* m_GLCache;

		// Some sort of list of entities (tied to models that are in the Renderer (should this be changed to Renderer3D?))
		//std::vector<Entity*> m_Entities;

		std::vector<graphics::Renderable3D*> m_Renderables;
		graphics::Shader m_TerrainShader, m_ModelShader, m_ShadowmapShader;

	public:
		Scene3D(graphics::FPSCamera* camera);
		~Scene3D();

		void add(graphics::Renderable3D* renderable);

		// Passes
		void shadowmapPass();

		void onUpdate(float deltaTime);
		void onRender(unsigned int shadowmap);

		inline graphics::MeshRenderer* getRenderer() const { return m_Renderer; }
		inline graphics::FPSCamera* getCamera() const { return m_Camera; }

	private:
		void init();

		void addObjectsToRenderQueue();

	};
}