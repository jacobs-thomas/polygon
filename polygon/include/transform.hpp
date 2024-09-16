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
		Matrix3x3f transformation;


	public:
		// Constants:
		static const Vector3f GLOBAL_UP;
		static const Vector3f GLOBAL_RIGHT;


		// Constructors:
		Transform() : transformation(Matrix3x3f(1.0f)), translation(Vector2f(0.0f)), scale(Vector2f(1.0f)), rotation(0.0f) {
			transformation = GetTransformationMatrix();
		}


		// Methods:
		const Matrix3x3f& GetTransformationMatrix() const {

			Matrix3x3f matrix = Matrix3x3f(1.0f);
			matrix = glm::translate(matrix, translation);
			matrix = glm::rotate(matrix, rotation);
			matrix = glm::scale(matrix, scale);

			return matrix;
		}

		inline const Vector2f GetTranslation() const {
			return translation;
		}

		const Vector2f SetTranslation(const Vector2f& translation) {
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
			Vector3f up = Vector3f(0.0f, 1.0f, 0.0f);

			// Multiply the rotation matrix with the 'up' vector
			Vector3f rotatedUp = transformation * GLOBAL_UP;

			// Epsilon threshold to clamp small values
			const float epsilon = 1e-6f;

			if (fabs(rotatedUp.x) < epsilon) rotatedUp.x = 0.0f;
			if (fabs(rotatedUp.y) < epsilon) rotatedUp.y = 0.0f;

			// Convert back to 2D by dropping the z component
			return Vector2f(rotatedUp.x, rotatedUp.y);
		}

		const Vector2f Right() const {
			// Define the 'up' vector (positive Y-axis in local space)
			Vector3f up = Vector3f(1.0f, 0.0f, 0.0f);

			// Multiply the rotation matrix with the 'up' vector
			Vector3f rotatedUp = transformation * GLOBAL_RIGHT;

			// Epsilon threshold to clamp small values
			const float epsilon = 1e-6f;

			if (fabs(rotatedUp.x) < epsilon) rotatedUp.x = 0.0f;
			if (fabs(rotatedUp.y) < epsilon) rotatedUp.y = 0.0f;

			// Convert back to 2D by dropping the z component
			return Vector2f(rotatedUp.x, rotatedUp.y);
		}
	};
}

#endif // !POLYGON_TRANSFORM_HPP
