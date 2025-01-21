#pragma once

#include "graphics/camera/ICamera.h"

namespace tiger {

		class CubemapCamera : public ICamera{
		public:
			CubemapCamera();
			CubemapCamera(glm::vec3& centerPosition);

			~CubemapCamera() = default;

			void switchCameraToFace(int cubeFaceIndex);
			inline void setCenterPosition(glm::vec3& newPosition) { m_CenterPosition = newPosition; }

			virtual glm::mat4 getViewMatrix() const override;
			virtual glm::mat4 getProjectionMatrix() const override;
			inline virtual const glm::vec3& getPosition() const override { return m_CenterPosition; }
			inline virtual const glm::vec3& getFront() const override { return m_Front; }
			inline virtual const glm::vec3& getUp() const override { return m_Up; }
			inline virtual void setPosition(const glm::vec3& position) override { m_CenterPosition = position; }
			inline virtual void invertPitch() override {}
		private:
			glm::vec3 m_CenterPosition, m_Front, m_Up;
		};
}