#include "Renderable3D.h"

namespace tiger {
	namespace graphics {

		Renderable3D::Renderable3D(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotationAxis, float radianRotation, Model* model)
			: m_Position(position), m_Scale(scale), m_RotationAxis(rotationAxis), m_RadianRotation(radianRotation), m_Model(model)
		{
		}

		Renderable3D::~Renderable3D() {

		}

		void Renderable3D::draw(Shader& shader) const {
			m_Model->Draw(shader);
		}
	}
}