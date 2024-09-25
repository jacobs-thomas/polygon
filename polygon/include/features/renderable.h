#ifndef POLYGON_RENDERABLE_H
#define POLYGON_RENDERABLE_H

#include "../sprite_renderer.h"
#include "feature.h"

namespace polygon {
    class Renderable : public Feature {
    private:
        // Instance Fields:
        SpriteRenderer spriteRenderer;
        Sprite sprite;
        std::shared_ptr<Shader> shader;

    public:
        // Constructor:
        Renderable() { }

        // Methods:
        inline void SetSprite(const Sprite& sprite) {
            this->sprite = sprite;
        }

        inline void SetShader(std::shared_ptr<Shader> shader) {
            this->shader = shader;
        }

        void OnInitialise(Context& scene) { }

        void OnTick(Context& context, float deltaTime);
    };
}

#endif // !POLYGON_RENDERABLE_H
