#include "DynamicLight.h"

namespace tiger {
	namespace graphics {

		DynamicLight::DynamicLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec)
			: ambient(amb), diffuse(diff), specular(spec), isActive(false) 
		{}

	}
}