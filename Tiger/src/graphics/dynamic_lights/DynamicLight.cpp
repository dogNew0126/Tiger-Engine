#include "DynamicLight.h"

namespace tiger {
	namespace graphics {

		DynamicLight::DynamicLight(const glm::vec3& lightColour)
			: lightColour(lightColour), isActive(false) {}

	}
}