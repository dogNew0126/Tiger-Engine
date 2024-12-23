#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../utils/Singleton.h"
#include <iostream>

namespace tiger {
	namespace graphics {

		class GLCache : utils::Singleton {
		public:

			GLCache();
			~GLCache();

			static GLCache* getInstance();

			void setDepthTest(bool choice);
			void setBlend(bool choice);
			void setCull(bool choice);

			void setDepthFunc(GLenum depthFunc);
			void setStencilTest(bool choice);
			void setStencilFunc(GLenum testFunc, int stencilFragValue, unsigned int stencilBitmask);
			void setStencilOp(GLenum stencilFailOperation, GLenum depthFailOperation, GLenum depthPassOperation);
			void setStencilWriteMask(unsigned int bitmask);

			void setBlendFunc(GLenum src, GLenum dst);
			void setCullFace(GLenum faceToCull);
			void switchShader(unsigned int shaderID);

			void setMultisample(bool choice);

		private:

			// Toggles
			bool m_DepthTest;
			bool m_StencilTest;
			bool m_Blend;
			bool m_Cull;
			bool m_Multisample;

			// Depth State
			GLenum m_DepthFunc;

			// Stencil State
			GLenum m_StencilTestFunc;
			int m_StencilFragValue;
			unsigned int m_StencilFuncBitmask;
			GLenum m_StencilFailOperation, m_DepthFailOperation, m_DepthPassOperation;
			unsigned int m_StencilWriteBitmask;

			// Blend State
			GLenum m_BlendSrc, m_BlendDst;

			// Culling State
			GLenum m_FaceToCull;

			// Active binds
			unsigned int m_ActiveShaderID;
		};
	}
}