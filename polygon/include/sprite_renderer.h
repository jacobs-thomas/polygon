#ifndef POLYGON_SPRITE_RENDERER_NEW_HPP
#define POLYGON_SPRITE_RENDERER_NEW_HPP

#include "sprite.h"
#include "shaders/shader.h"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>                   // For vec3 and mat4 types
#include <glm/gtc/matrix_transform.hpp>   // For translate, rotate, scale functions

namespace polygon {

    class SpriteRenderer {
    private:
        // Instance Fields:
        unsigned int quadVAO;

        // Constants:
        const float DEFAULT_VERTICES[24] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,  // Top-left
            1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right
            0.0f, 0.0f, 0.0f, 0.0f,  // Bottom-left

            0.0f, 1.0f, 0.0f, 1.0f,  // Top-left
            1.0f, 1.0f, 1.0f, 1.0f,  // Top-right
            1.0f, 0.0f, 1.0f, 0.0f   // Bottom-right
        };

    public:
        // Constructor:
        SpriteRenderer() {

            // Initialize VAO/VBO setup
            unsigned int VBO;

            glGenVertexArrays(1, &this->quadVAO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(DEFAULT_VERTICES), DEFAULT_VERTICES, GL_STATIC_DRAW);

            glBindVertexArray(this->quadVAO);

            // Position attribute
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);  // 2 floats for position

            // Texture coordinate attribute
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));  // 2 floats for texCoords

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        // Methods:
        void DrawSprite(std::shared_ptr<Shader> shader, const Sprite& sprite, const Matrix4x4f& globalTransform) {

            if (auto texture = sprite.GetTexture().lock()) {
                // Base model matrix from transform (now using 4x4 matrix)
                Matrix4x4f model = globalTransform; // Make sure this returns a 4x4 matrix

                // Centering calculations
                Matrix4x4f centeringMatrix = Matrix4x4f(1.0f);

                // Translate to center the sprite
                centeringMatrix = glm::translate(centeringMatrix, Vector3f(-0.5f * sprite.GetSize().x, -0.5f * sprite.GetSize().y, 0.0f));

                // Scale the sprite
                centeringMatrix = glm::scale(centeringMatrix, Vector3f(sprite.GetSize(), 1.0f));

                // Apply model transformation
                centeringMatrix = model * centeringMatrix;

                // Prepare for rendering
                shader->Use();
                shader->SetMatrix4f("model", centeringMatrix);
                shader->SetVector3f("spriteColor", Vector3f(1.0f, 1.0f, 1.0f));

                glActiveTexture(GL_TEXTURE0);
                texture->Bind();

                glBindVertexArray(quadVAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);
            }
        }
    };
}

#endif // !POLYGON_SPRITE_RENDERER_NEW_HPP
