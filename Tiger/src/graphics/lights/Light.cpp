#include "pch.h"
#include "Light.h"

namespace tiger {

		Light::Light(const glm::vec3& lightColour)
			: m_LightColour(lightColour), m_IsStatic(false) {}

}