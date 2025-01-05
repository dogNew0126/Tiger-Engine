#pragma once

#include "Light.h"

namespace tiger {

	class DynamicLightManager;

	class PointLight : public Light {
		friend DynamicLightManager;

	public:
		PointLight(const glm::vec3& lightColour, const glm::vec3& pos);

		virtual void setupUniforms(Shader* shader, int currentLightIndex) override;

	private:
		glm::vec3 m_Position;
	};

}