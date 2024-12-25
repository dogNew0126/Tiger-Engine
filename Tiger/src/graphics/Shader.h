#pragma once

#include "../utils/FileUtils.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tiger {
	namespace graphics {

		class Shader {
		private: 
			unsigned int m_ShaderID;
			const char* m_VertPath, * m_FragPath, * m_GeomPath;

		public:

			Shader(const char *vertPath, const char *fragPath);

			Shader(const char* vertPath, const char* fragPath, const char* geoPath);
			~Shader();

			void setUniform1f(const char* name, float value);
			void setUniform1i(const char* name, int value);
			void setUniform2f(const char* name, const glm::vec2& vector);
			void setUniform3f(const char* name, const glm::vec3& vector);
			void setUniform4f(const char* name, const glm::vec4& vector);
			void setUniformMat3(const char* name, const glm::mat3& matrix);
			void setUniformMat4(const char* name, const glm::mat4& matrix);

			void enable() const;
			void disable() const;

			inline unsigned int getShaderID() const { return m_ShaderID; }

		private:

			int getUniformLocation(const char* name);

			unsigned int load();
		};
	}
}