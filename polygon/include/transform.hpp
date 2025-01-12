#ifndef POLYGON_TRANSFORM_HPP
#define POLYGON_TRANSFORM_HPP


#define GLM_ENABLE_EXPERIMENTAL


#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include "type_definitions.hpp"


namespace polygon {

	class Transform {
	private:
		// Instance Attributes:
		Vector2f translation;
		Vector2f scale;
		float rotation;
		Matrix4x4f transformation;


	public:
		// Constants:
		static const Vector3f GLOBAL_UP;
		static const Vector3f GLOBAL_RIGHT;


		// Constructors:
		Transform() : transformation(Matrix3x3f(1.0f)), translation(Vector2f(0.0f)), scale(Vector2f(1.0f)), rotation(0.0f) {
			transformation = GetTransformationMatrix();
		}


		// Methods:
		const Matrix4x4f& GetTransformationMatrix() {

			transformation = Matrix4x4f(1.0f);

			// Apply transformations
			transformation = glm::translate(transformation, Vector3f(translation, 0.0f)); // Translation in 2D (with z=0)
			transformation = glm::rotate(transformation, rotation, Vector3f(0.0f, 0.0f, 1.0)); // Rotation around Z-axis
			scale.y = -1.0f; // Flip the scale.y to compensate for flipped y axis.
			transformation = glm::scale(transformation, Vector3f(scale, 1.0f)); // 1.0f for z-axis

			return transformation;  // Return by value, not reference
		}

		inline const Vector2f GetTranslation() const {
			return translation;
		}

		void SetTranslation(const Vector2f& translation) {
			this->translation = translation;
			transformation = GetTransformationMatrix();
		}

		inline const float GetRotation() const {
			return rotation;
		}

		void SetRotation(float radians) {
			this->rotation = radians;
			transformation = GetTransformationMatrix();
		}

		inline const Vector2f GetScale() const {
			return scale;
		}

		void SetScale(const Vector2f& scale) {
			this->scale = scale;
			transformation = GetTransformationMatrix();
		}

		const Vector2f Up() const {

			// Define the 'up' vector (positive Y-axis in local space)
			Vector4f up = Vector4f(0.0f, 1.0f, 0.0f, 0.0f); // w = 0.0 for direction

			// Multiply the rotation matrix with the 'up' vector
			Vector3f rotatedUp = transformation * up;

			// Epsilon threshold to clamp small values
			const float epsilon = 1e-6f;

			if (fabs(rotatedUp.x) < epsilon) rotatedUp.x = 0.0f;
			if (fabs(rotatedUp.y) < epsilon) rotatedUp.y = 0.0f;

			// Convert back to 2D by dropping the z component
			return Vector2f(rotatedUp.x, rotatedUp.y);
		}

		const Vector2f Right() const {
			// Define the 'right' vector (positive X-axis in local space)
			Vector4f right = Vector4f(1.0f, 0.0f, 0.0f, 0.0f); // w = 0.0 for direction

			// Multiply the transformation matrix with the 'right' vector
			Vector4f rotatedRight = transformation * right;

			// Epsilon threshold to clamp small values
			const float epsilon = 1e-6f;

			if (fabs(rotatedRight.x) < epsilon) rotatedRight.x = 0.0f;
			if (fabs(rotatedRight.y) < epsilon) rotatedRight.y = 0.0f;

			// Convert back to 2D by dropping the z component
			return Vector2f(rotatedRight.x, rotatedRight.y);
		}
	};
}

#endif // !POLYGON_TRANSFORM_HPP
