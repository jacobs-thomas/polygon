#include "renderable.h"
#include "../transform.h"
#include "../nodes/node.h"

polygon::Matrix4x4f GetTransformMatrix(polygon::Transform localTransform) {

	polygon::Matrix4x4f matrix = polygon::Matrix4x4f(1.0f);

	// Apply transformations
	matrix = glm::translate(matrix, polygon::Vector3f(localTransform.translation, 0.0f)); // Translation in 2D (with z=0)
	matrix = glm::rotate(matrix, localTransform.rotation, polygon::Vector3f(0.0f, 0.0f, 1.0)); // Rotation around Z-axis
	localTransform.scale.y = -1.0f; // Flip the scale.y to compensate for flipped y axis.
	matrix = glm::scale(matrix, polygon::Vector3f(localTransform.scale, 1.0f)); // 1.0f for z-axis

	return matrix; // Return by value, not reference
}

void polygon::Renderable::OnTick(Context& context, float deltaTime) {
	spriteRenderer.DrawSprite(shader, sprite, GetTransformMatrix(possessor->GetGlobalTransform()));
}