#pragma once

#include "DynamicLight.h"

namespace tiger {

		struct PointLight : public DynamicLight {

		public:
			PointLight(const glm::vec3& lightColour, const glm::vec3& pos);

			virtual void setupUniforms(Shader& shader, int currentLightIndex) override;
			glm::vec3 position;
		};

}