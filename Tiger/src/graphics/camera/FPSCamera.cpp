#include "pch.h"
#include "FPSCamera.h"
#include "graphics/Window.h"
#include "ui/DebugPane.h"

namespace tiger {

		FPSCamera::FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
			: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_FOV(FOV), 
				m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch)
		{
			updateCameraVectors();
		}

		FPSCamera::FPSCamera(float xPos, float yPos, float zPos, float xUp, float yUp, float zUp, float yaw = YAW, float pitch = PITCH)
			: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_FOV(FOV),
				m_Position(glm::vec3(xPos, yPos, zPos)), m_WorldUp(glm::vec3(xUp, yUp, zUp)), m_Yaw(yaw), m_Pitch(pitch)
		{
			updateCameraVectors();
			DebugPane::bindCameraPositionValue(&m_Position);
		}

		glm::mat4 FPSCamera::getViewMatrix() const {
			return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}

		glm::mat4 FPSCamera::getProjectionMatrix() const {
			return glm::perspective(glm::radians(m_FOV), (float)Window::getWidth() / (float)Window::getHeight(), NEAR_PLANE, FAR_PLANE);
		}

		void FPSCamera::processInput(float deltaTime) {
			// Keyboard input
			if (InputManager::isKeyPressed(GLFW_KEY_W))
				processKeyboard(tiger::FORWARD, deltaTime);
			if (InputManager::isKeyPressed(GLFW_KEY_S))
				processKeyboard(tiger::BACKWARD, deltaTime);
			if (InputManager::isKeyPressed(GLFW_KEY_A))
				processKeyboard(tiger::LEFT, deltaTime);
			if (InputManager::isKeyPressed(GLFW_KEY_D))
				processKeyboard(tiger::RIGHT, deltaTime);
			if (InputManager::isKeyPressed(GLFW_KEY_SPACE))
				processKeyboard(tiger::UPWARDS, deltaTime);
			if (InputManager::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
				processKeyboard(tiger::DOWNWARDS, deltaTime);
			if (InputManager::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
				m_MovementSpeed = SPEED * 4.0f;
			else if (InputManager::isKeyPressed(GLFW_KEY_LEFT_ALT))
				m_MovementSpeed = SPEED / 4.0f;
			else
				m_MovementSpeed = SPEED;
			// Mouse scrolling
			processMouseScroll(InputManager::getScrollY() * 6);
			// Mouse movement
			processMouseMovement(InputManager::getMouseXDelta(), -InputManager::getMouseYDelta(), true);
		}

		void FPSCamera::processKeyboard(Camera_Movement direction, float deltaTime) 
		{
			float velocity = m_MovementSpeed * deltaTime;
			switch (direction) {
			case FORWARD:
				m_Position += m_Front * velocity;
				break;
			case BACKWARD:
				m_Position -= m_Front * velocity;
				break;
			case LEFT:
				m_Position -= m_Right * velocity;
				break;
			case RIGHT:
				m_Position += m_Right * velocity;
				break;
			case UPWARDS:
				m_Position += m_WorldUp * velocity;
				break;
			case DOWNWARDS:
				m_Position -= m_WorldUp * velocity;
				break;
			}
		}

		void FPSCamera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
		{
			// Make sure the user isn't interacting with the UI
			if (!Window::getHideCursor())
				return;
			xOffset *= m_MouseSensitivity;
			yOffset *= m_MouseSensitivity;
			m_Yaw += xOffset;
			m_Pitch += yOffset;
			// Constrain the pitch
			if (constrainPitch) {
				if (m_Pitch > 89.0f) {
					m_Pitch = 89.0f;
				}
				else if (m_Pitch < -89.0f) {
					m_Pitch = -89.0f;
				}
			}
			updateCameraVectors();
		}

		void FPSCamera::processMouseScroll(float offset) {
			if (offset != 0 && m_FOV >= 1.0f && m_FOV <= FOV) {
				m_FOV -= offset;
			}
			if (m_FOV < 1.0f) {
				m_FOV = 1.0f;
			}
			else if (m_FOV > FOV) {
				m_FOV = FOV;
			}
		}

		void FPSCamera::updateCameraVectors() {
			glm::vec3 front;
			front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			front.y = sin(glm::radians(m_Pitch));
			front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			m_Front = glm::normalize(front);

			// Recalculate Vectors
			m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
			m_Up = glm::normalize(glm::cross(m_Right, m_Front));
		}

}