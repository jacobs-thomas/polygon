#ifndef POLYGON_TEXTURE_2D_HPP
#define POLYGON_TEXTURE_2D_HPP

#include <gl/glew.h>
#include <iostream>


namespace polygon {

	class Resource {
	public:
		virtual ~Resource() = default; 
	};


	class Texture2D : public Resource {
	private:
		// Instance Attributes:
		int width;
		int height;
		int nrChannels;
		const char* filename;
		unsigned int ID;


	public:
		// Constructor:
        Texture2D(const char* filename);


		// Methods:
		inline void Bind() const {
			glBindTexture(GL_TEXTURE_2D, ID);
		}

		inline const int GetWidth() const {
			return width;
		}

		inline const int GetHeight() const {
			return height;
		}

		inline const char* GetFilename() const {
			return filename;
		}
	};
}


#endif // !POLYGON_TEXTURE_2D_HPP
