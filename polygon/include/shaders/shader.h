#ifndef POLYGON_SHADER_H
#define POLYGON_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/mat4x4.hpp>
#include "../type_definitions.hpp"

namespace polygon {

	class Shader {

	public:
		// Instance Attribute:
		unsigned int ID;

		// Constructor:
		Shader(const char* vertexPath, const char* fragmentPath);

		// Methods:
		void Use();
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float) const;
		void SetVector3f(const std::string& name, Vector3f value) const;
		void SetMatrix4f(const std::string& name, glm::mat4 value) const;
	};

}

#endif // !POLYGON_SHADER_H

