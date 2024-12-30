#pragma once

#include "DynamicLight.h"

namespace tiger {

		struct SpotLight : public DynamicLight {

		public:
			SpotLight(const glm::vec3& lightColour, const glm::vec3& pos, const glm::vec3& dir, float cutOffAngle, float outerCutOffAngle);

			virtual void setupUniforms(Shader& shader, int currentLightIndex) override;
			glm::vec3 position, direction;
			float cutOff, outerCutOff;
		};

}