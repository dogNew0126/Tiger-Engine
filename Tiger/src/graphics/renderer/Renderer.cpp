#include "Renderer.h"


namespace tiger {
	namespace graphics {

		Renderer::Renderer(Camera* camera) : m_Camera(camera)
		{

		}

		void Renderer::submitOpaque(Renderable3D* renderable) {
			m_OpaqueRenderQueue.push_back(renderable);
		}

		void Renderer::submitTransparent(Renderable3D* renderable) {
			m_TransparentRenderQueue.push_back(renderable);
		}

		void Renderer::flushOpaque(Shader& shader, Shader& outlineShader) {

			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			// Render opaque objects
			while (!m_OpaqueRenderQueue.empty()) {

				// Drawing prepration
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
				glStencilFunc(GL_ALWAYS, 1, 0xFF);
				glStencilMask(0xFF);

				Renderable3D* current = m_OpaqueRenderQueue.front();

				setupModelMatrix(current, shader);
				current->draw(shader);

				if (current->getShouldOutline()) {

					drawOutline(outlineShader, current);
					shader.enable();

				}


				m_OpaqueRenderQueue.pop_front();
			}
		}

		void Renderer::flushTransparent(Shader& shader, Shader& outlineShader) {

			// Sort then render transparent objects (from back to front)

			glDisable(GL_CULL_FACE); // Don't backface cull transparent objects

			std::sort(m_TransparentRenderQueue.begin(), m_TransparentRenderQueue.end(),
				[this](Renderable3D* a, Renderable3D* b) -> bool
			{
				return glm::length2(m_Camera->getPosition() - a->getPosition()) > glm::length2(m_Camera->getPosition() - b->getPosition());
			});

			// Sort then render transparent objects
			while (!m_TransparentRenderQueue.empty()) {

				// Drawing prepration
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
				glStencilFunc(GL_ALWAYS, 1, 0xFF);
				glStencilMask(0xFF);

				// Enable blending (note: You will still need to sort from back to front when rendering)
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Tell OpenGL how to blend, in this case make the new object have the transparency of its alpha and the object in the back is 1-alpha
				
				Renderable3D* current = m_TransparentRenderQueue.front();
				setupModelMatrix(current, shader);
				current->draw(shader);

				// Draw the outline
				if (current->getShouldOutline()) {

					drawOutline(outlineShader, current);

					shader.enable();
				}

				glDisable(GL_BLEND);

				m_TransparentRenderQueue.pop_front();
			}
		}

		// TODO: Currently only support two levels in a hierarchical scene graph
		void Renderer::setupModelMatrix(Renderable3D* renderable, Shader& shader, float scaleFactor) {
			glm::mat4 model(1);
			glm::mat4 translate = glm::translate(glm::mat4(1.0f), renderable->getPosition());
			glm::mat4 rotate = glm::toMat4(renderable->getOrientation());
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), renderable->getScale() * scaleFactor);

			if (!renderable->getParent()) {
				model = translate * rotate * scale;
			}
			else {
				// Only apply scale locally
				model = glm::translate(glm::mat4(1.0f), renderable->getParent()->getPosition()) * glm::toMat4(renderable->getParent()->getOrientation()) * translate * rotate * scale;
			}

			shader.setUniformMat4("model", model);
		}

		void Renderer::drawOutline(Shader& outlineShader, Renderable3D* renderable) {

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

			outlineShader.enable();
			setupModelMatrix(renderable, outlineShader, 1.005f);

			renderable->draw(outlineShader);
			outlineShader.disable();

			glEnable(GL_DEPTH_TEST);
			glStencilMask(0xFF);

			glClear(GL_STENCIL_BUFFER_BIT);
		}


	}
}