#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Defs.h"
#include "../utils/Logger.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace tiger {
	namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

		class Window {
		private:
			const char* m_Title;
			GLFWwindow* m_Window;

			static int s_Width, s_Height;
			static bool s_Keys[MAX_KEYS];
			static bool s_Buttons[MAX_BUTTONS];
			static double s_MouseX, s_MouseY, s_MouseXDelta, s_MouseYDelta;
			static double s_ScrollX, s_ScrollY;

		public:

			/**
			* Creates a window and allows for raw input to be handled
			* Will properly close resources if the window was not initialized properly
			*
			* @param title The title of the window
			* @param width The width of the window
			* @param height The height of the window
			*/
			Window(const char* title, int width, int height);
			~Window();

			/**
			* Will swap the screen buffers and will poll all window/input events
			*/
			void update();

			/**
			* Clears the screen using the following masks: GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
			*/
			void clear() const;

			/**
			* @return returns true if the window is closed or being closed
			*/
			bool closed() const;

			/**
			* checks if a key is being pressed
			*
			* @param keycode The keycode of the key that you want to check if it is being pressed
			* @return returns true if the key is being pressed
			*/
			static bool isKeyPressed(unsigned int keycode);

			/**
			* checks if a mouse button is being pressed
			*
			* @param code The code of the mouse button that you want to check if it is being pressed
			* @return returns true if the mouse button is being pressed
			*/
			static bool isMouseButtonPressed(unsigned int code);

			// Getters and setters
			static inline double getMouseX() { return s_MouseX; }
			static inline double getMouseY() { return s_MouseY; }
			static inline double getMouseXDelta() { return s_MouseXDelta; }
			static inline double getMouseYDelta() { return s_MouseYDelta; }
			static inline double getScrollX() { return s_ScrollX; }
			static inline double getScrollY() { return s_ScrollY; }
			static inline void resetScroll() { s_ScrollX = 0; s_ScrollY = 0; }
			static inline void getMousePosition(double& x, double& y) { x = s_MouseX; y = s_MouseY; }
			static inline int getWidth() { return s_Width; }
			static inline int getHeight() { return s_Height; }

		private:
			/**
			* Creates the window. Sets up the mouse settings and all important callbacks
			* Initializes GLEW and initializes v-sync depending on the settings
			*
			* @return returns true if the window was initialized properly
			*/
			bool init();

			/**
			* Sets the size of the window to the resolution of the primary monitor
			*/
			void setFullScreenResolution();
		};

	}
}