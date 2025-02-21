#pragma once

#include "graphics/Shader.h"

namespace tiger {

		class Light {
		public:
			Light(float lightIntensity, const glm::vec3& lightColour);

			virtual void setupUniforms(Shader* shader, int currentLightIndex) = 0;

		protected:
			float m_Intensity;
			glm::vec3 m_LightColour;
			bool m_IsStatic;
		};
}