#pragma once

#include "graphics/mesh/Model.h"
#include "graphics/camera/FPSCamera.h"
#include "scene/RenderableModel.h"
#include "GLCache.h"
#include "graphics/mesh/common/Quad.h"


namespace tiger {

	class MeshRenderer {
	public:

		MeshRenderer(FPSCamera* camera);

		void submitOpaque(RenderableModel* renderable);
		void submitTransparent(RenderableModel* renderable);

		void flushOpaque(Shader& shader, RenderPass pass);
		void flushTransparent(Shader& shader, RenderPass pass);

	public:
		Quad NDC_Plane;

	private:

		void setupModelMatrix(RenderableModel* renderable, Shader& shader, RenderPass pass);

		std::deque<RenderableModel*> m_OpaqueRenderQueue;
		std::deque<RenderableModel*> m_TransparentRenderQueue;

		FPSCamera* m_Camera;
		GLCache* m_GLCache;

	};

}