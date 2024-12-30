#pragma once

namespace tiger
{
	class ICamera
	{
	public:
		virtual ~ICamera() {}
		virtual glm::mat4 getViewMatrix() const = 0;
		virtual glm::mat4 getProjectionMatrix() const = 0;
		virtual const glm::vec3& getPosition() const = 0;
		virtual const glm::vec3& getFront() const = 0;
		virtual const glm::vec3& getUp() const = 0;
	};
}