#pragma once

#include "../Model.h"
#include <glm/glm.hpp>

namespace tiger {
	namespace graphics {

		class Renderable3D {

		public:
			Renderable3D(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotationAxis, float radianRotation, Model* model, Renderable3D* parent, bool shouldOutline = false, bool transparent = false);
			~Renderable3D();

			void draw(Shader& shader) const;

			inline const glm::vec3& getPosition() const { return m_Position; }
			inline const glm::vec3& getScale() const { return m_Scale; }
			inline const glm::quat& getOrientation() const { return m_Orientation; }
			inline const Renderable3D* getParent() const { return m_Parent; }
			inline bool getShouldOutline() const { return m_ShouldOutline; }
			inline bool getTransparent() const { return m_Transparent; }

			inline void setPosition(glm::vec3& other) { m_Position = other; }
			inline void setScale(glm::vec3& other) { m_Scale = other; }
			inline void setShouldOutline(bool value) { m_ShouldOutline = value; }
			inline void setTransparent(bool value) { m_Transparent = value; }

		private:

			glm::vec3 m_Position, m_Scale;
			glm::quat m_Orientation;
			Renderable3D* m_Parent;
			bool m_ShouldOutline, m_Transparent;

			Model* m_Model;
		};

	}
}