#ifndef POLYGON_MESH_H
#define POLYGON_MESH_H


#include "vertex.hpp"
#include "texture.hpp"
#include "../shaders/shader.h"
#include <vector>


namespace polygon {
	class Mesh {
	private:
		// Instance Attributes:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		unsigned int VAO, VBO, EBO;

	public:
		// Constructor:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> texture);

		// Methods:
		void Draw(Shader& shader);

	private:
		// Methods:
		void SetupMesh();
	};
}


#endif // !POLYGON_MESH_H

