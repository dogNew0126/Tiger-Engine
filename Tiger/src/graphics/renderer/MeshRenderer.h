#pragma once

#include "graphics/mesh/Model.h"
#include "graphics/camera/FPSCamera.h"
#include "scene/SceneNode.h"
#include "GLCache.h"
#include "graphics/mesh/common/Quad.h"


namespace tiger {
	namespace graphics {

		class MeshRenderer {
		public:

			MeshRenderer(FPSCamera* camera);

			void submitOpaque(scene::SceneNode* renderable);
			void submitTransparent(scene::SceneNode* renderable);

			void flushOpaque(Shader& shader, RenderPass pass);
			void flushTransparent(Shader& shader, RenderPass pass);

		public:
			Quad NDC_Plane;

		private:

			void setupModelMatrix(scene::SceneNode* renderable, Shader& shader, RenderPass pass);

			std::deque<scene::SceneNode*> m_OpaqueRenderQueue;
			std::deque<scene::SceneNode*> m_TransparentRenderQueue;

			FPSCamera* m_Camera;
			GLCache* m_GLCache;

		};

	}
}