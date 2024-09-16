#ifndef POLYGON_TEXTURE_HPP
#define POLYGON_TEXTURE_HPP

#include <string>


namespace polygon {

	struct Texture {
	public:
		unsigned int id;
		std::string type;

		// Constructor:
		Texture(unsigned int id, std::string type) : id(id), type(type) {

		}
	};
}


#endif // !POLYGON_TEXTURE_HPP
