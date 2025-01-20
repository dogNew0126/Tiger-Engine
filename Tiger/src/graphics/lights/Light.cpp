#include "pch.h"
#include "Light.h"

namespace tiger {

		Light::Light(float lightIntensity, const glm::vec3& lightColour)
			: m_Intensity(lightIntensity), m_LightColour(lightColour), m_IsStatic(false) {}

}