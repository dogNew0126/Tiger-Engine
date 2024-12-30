#pragma once

#include "graphics/mesh/Model.h"
#include "graphics/camera/FPSCamera.h"
#include "scene/RenderableModel.h"
#include "GLCache.h"
#include "graphics/mesh/common/Quad.h"
#include "graphics/renderer/renderpass/RenderPassType.h"


namespace tiger {

	class ModelRenderer {
	public:

		ModelRenderer(FPSCamera* camera);

		void submitOpaque(RenderableModel* renderable);
		void submitTransparent(RenderableModel* renderable);

		void flushOpaque(Shader* shader, RenderPassType pass);
		void flushTransparent(Shader* shader, RenderPassType pass);

	public:
		Quad NDC_Plane;

	private:

		void setupModelMatrix(RenderableModel* renderable, Shader* shader, RenderPassType pass);

		std::deque<RenderableModel*> m_OpaqueRenderQueue;
		std::deque<RenderableModel*> m_TransparentRenderQueue;

		FPSCamera* m_Camera;
		GLCache* m_GLCache;

	};

}