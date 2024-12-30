#pragma once

#include "graphics/mesh/Model.h"
#include "graphics/camera/FPSCamera.h"
#include "scene/Renderable3D.h"
#include "GLCache.h"
#include "graphics/mesh/common/Quad.h"


namespace tiger {

	class MeshRenderer {
	public:

		MeshRenderer(FPSCamera* camera);

		void submitOpaque(Renderable3D* renderable);
		void submitTransparent(Renderable3D* renderable);

		void flushOpaque(Shader& shader, RenderPass pass);
		void flushTransparent(Shader& shader, RenderPass pass);

	public:
		Quad NDC_Plane;

	private:

		void setupModelMatrix(Renderable3D* renderable, Shader& shader, RenderPass pass);

		std::deque<Renderable3D*> m_OpaqueRenderQueue;
		std::deque<Renderable3D*> m_TransparentRenderQueue;

		FPSCamera* m_Camera;
		GLCache* m_GLCache;

	};

}