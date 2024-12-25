#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>

#include "../graphics/mesh/Mesh.h"
#include "../graphics/mesh/Model.h"

namespace tiger {
	namespace terrain {

		class Terrain {

		public:
			Terrain(const glm::vec3& worldPosition);
			~Terrain();

			void Draw(graphics::Shader& shader, graphics::RenderPass pass) const;

			inline const glm::vec3& getPosition() const { return m_Position; }

		private:

			glm::vec3 calculateNormal(int x, int z, unsigned char* heightMapData);
			float getVertexHeight(int x, int y, unsigned char* heightMapData);

			float m_TerrainSize;
			unsigned int m_VertexSideCount;
			GLushort m_HeightMapScale;
			glm::mat4 m_ModelMatrix;
			glm::vec3 m_Position;
			graphics::Mesh* m_Mesh;
			std::array<graphics::Texture*, 5> m_Textures; // Represents all the textures supported by the terrain's texure splatting (rgba and the default value)

		};

	}
}