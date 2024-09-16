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


namespace polygon {
	typedef glm::vec<2, float> Vector2f;
	typedef glm::vec<3, float> Vector3f;
	typedef glm::mat<3, 3, float> Matrix3x3f;
}

#endif // !POLGON_TYPE_DEFINITIONS