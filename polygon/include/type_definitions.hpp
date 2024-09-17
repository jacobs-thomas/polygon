#ifndef POLGON_TYPE_DEFINITIONS
#define POLGON_TYPE_DEFINITIONS


#include <iostream>
#include <vector>
#include <assert.h>
#include <type_traits>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <memory>
#include <vector>
#include <cassert>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>                   // For vec3 and mat4 types
#include <glm/gtc/matrix_transform.hpp> 

namespace polygon {
	typedef glm::vec<2, float> Vector2f;
	typedef glm::vec<3, float> Vector3f;
	typedef glm::vec<4, float> Vector4f;
	typedef glm::mat<3, 3, float> Matrix3x3f;
	typedef glm::mat<4, 4, float> Matrix4x4f;
}

#endif // !POLGON_TYPE_DEFINITIONS