#ifndef POLYGON_SPRITE_H
#define POLYGON_SPRITE_H

#include "texture2D.hpp"
#include "type_definitions.hpp"

namespace polygon {

	class Sprite {
	private:
		std::weak_ptr<Texture2D> texture;
		Vector2f size = Vector2f(0.0f,0.0f);

	public:
		Vector3f color = Vector3f(1.0f, 1.0f, 1.0f);

		// Constructor:
		Sprite() {

		}

		Sprite(std::weak_ptr<Texture2D> texture) {

			this->texture = texture;

			if (auto texturePtr = texture.lock()) {
				size = Vector2f(texturePtr->GetWidth(), texturePtr->GetHeight());
			}
		}

		inline std::weak_ptr<Texture2D> GetTexture() const { return texture; }
		inline const Vector2f& GetSize() const { return size; }
	};
}

#endif // !POLYGON_SPRITE_H
