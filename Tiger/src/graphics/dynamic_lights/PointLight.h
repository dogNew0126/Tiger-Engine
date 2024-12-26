#pragma once

#include "DynamicLight.h"

#include <string>

namespace tiger {
	namespace graphics {

		struct PointLight : public DynamicLight {

		public:
			PointLight(const glm::vec3& lightColour, const glm::vec3& pos);

			virtual void setupUniforms(Shader& shader, int currentLightIndex) override;
			glm::vec3 position;
		};
	}
}