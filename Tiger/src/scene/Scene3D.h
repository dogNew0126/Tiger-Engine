#pragma once

#include "scene/Renderable3D.h"
#include "graphics/camera/FPSCamera.h"
#include "graphics/renderer/MeshRenderer.h"
#include "graphics/renderer/GLCache.h"
#include "terrain/Terrain.h"
#include "graphics/Window.h"
#include "graphics/Skybox.h"
#include "graphics/dynamic_lights/DynamicLightManager.h"

namespace tiger {

	class Scene3D {

	private:
		FPSCamera* m_Camera;
		MeshRenderer* m_Renderer;
		Terrain* m_Terrain;
		Skybox* m_Skybox;
		DynamicLightManager m_DynamicLightManager;
		GLCache* m_GLCache;

		// Some sort of list of entities (tied to models that are in the Renderer (should this be changed to Renderer3D?))
		//std::vector<Entity*> m_Entities;

		std::vector<Renderable3D*> m_Renderables;
		Shader m_TerrainShader, m_ModelShader, m_ShadowmapShader;

	public:
		Scene3D(FPSCamera* camera);
		~Scene3D();

		void add(Renderable3D* renderable);

		// Passes
		void shadowmapPass();

		void onUpdate(float deltaTime);
		void onRender(unsigned int shadowmap);

		inline MeshRenderer* getRenderer() const { return m_Renderer; }
		inline FPSCamera* getCamera() const { return m_Camera; }

	private:
		void init();

		void addObjectsToRenderQueue();

	};
}