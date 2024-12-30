#include "pch.h"
#include "RenderableModel.h"

namespace tiger {

	RenderableModel::RenderableModel(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotationAxis, float radianRotation, Model* model, RenderableModel* parent, bool isStatic, bool isTransparent)
		: m_Position(position), m_Scale(scale), m_Orientation(glm::angleAxis(radianRotation, rotationAxis)), m_Model(model), m_Parent(parent), m_Transparent(isTransparent)
	{
	}

	RenderableModel::~RenderableModel() {
		// Recursive delete on children
		for (int i = 0; i < m_Children.size(); i++) {
			delete m_Children[i];
		}
	}

	void RenderableModel::draw(Shader* shader, RenderPassType pass) const {
		if (m_Model)
			m_Model->Draw(shader, pass);
	}

	void RenderableModel::addChild(RenderableModel* child) {
		if (child == this)
			return;

		m_Children.push_back(child);
		child->setParent(this);
	}

}