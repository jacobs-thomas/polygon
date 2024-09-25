
#include "transform.h"

const polygon::Vector3f polygon::Transform::GLOBAL_UP = Vector3f(0.0f, 1.0f, 0.0f);
const polygon::Vector3f polygon::Transform::GLOBAL_RIGHT = Vector3f(1.0f, 0.0f, 0.0f);


polygon::Transform polygon::Transform::operator*(const Transform& left) const {
	
	Transform result = *this;

	result.translation += left.translation;
	result.rotation += left.rotation;
	result.scale * left.scale;

	return result;
}

void polygon::Transform::operator*=(const Transform& left) {

	translation += left.translation;
	rotation += left.rotation;
	scale *= left.scale;
}