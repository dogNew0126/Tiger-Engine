#pragma once

#include "graphics/Shader.h"

namespace tiger {

		// TODO: Add functionality so it can update with an entitie's position and orientation
		struct DynamicLight {

			DynamicLight(const glm::vec3& lightColour);

			virtual void setupUniforms(Shader* shader, int currentLightIndex) = 0;

			glm::vec3 lightColour;
			bool isActive;
		};
}