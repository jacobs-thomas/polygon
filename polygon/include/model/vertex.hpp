#ifndef POLYGON_VERTEX_HPP
#define POLYGON_VERTEX_HPP


#include "../type_definitions.hpp"


namespace polygon {

	struct Vertex {
	
	public:
		// Instance Attributes:
		Vector3f position;
		Vector3f normal;
		Vector2f textureCoordinate;

		// Constructor:
		Vertex(Vector3f position, Vector3f normal, Vector3f textureCoordinates) : position(position), normal(normal), textureCoordinate(textureCoordinate) {

		}
	};
}

#endif // !POLYGON_VERTEX_HPP
