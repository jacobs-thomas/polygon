#ifndef POLYGON_SPRITE_RENDERER_NODE_HPP
#define POLYGON_SPRITE_RENDERER_NODE_HPP


#include "../node.hpp"
#include "../shaders/shader.h"
#include "../texture2D.hpp"
#include "../type_definitions.hpp"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>                   // For vec3 and mat4 types
#include <glm/gtc/matrix_transform.hpp>   // For translate, rotate, scale functions


namespace polygon {

	class SpriteRendererNode : public Node2D {

	private:
		Shader* shader;
		Texture2D* texture;
        unsigned int quadVAO;
		Vector2f size;


	public:
        // Constructor:
        SpriteRendererNode(Shader* shader, Texture2D* texture) : shader(shader), texture(texture) {
            
			InitialiseRenderData();

			if (texture == nullptr) { return; }

			size = Vector2f(texture->GetWidth(), texture->GetHeight());
        }


		// Methods:
		virtual void OnInitialise(Scene& scene) override {

		}

		virtual void OnTick(Scene& scene, const float deltaTime) override { 

            if (shader == nullptr || texture == nullptr) {
                return;
            }

            // Base model matrix from transform (now using 4x4 matrix)
            Matrix4x4f model = transform.GetTransformationMatrix(); // Make sure this returns a 4x4 matrix

            // Centering calculations
            Matrix4x4f centeringMatrix = Matrix4x4f(1.0f);

            // Translate to center the sprite
            centeringMatrix = glm::translate(centeringMatrix, Vector3f(-0.5f * size.x, -0.5f * size.y, 0.0f));

            // Scale the sprite
            centeringMatrix = glm::scale(centeringMatrix, Vector3f(size, 1.0f));

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


		// Destructor:
		~SpriteRendererNode() {

            glDeleteVertexArrays(1, &quadVAO);

			Node::~Node();
		}

	private:
		// Methods:
        void InitialiseRenderData() {
            // configure VAO/VBO
            unsigned int VBO;
            float vertices[] = {
                // pos      // tex
                0.0f, 1.0f, 0.0f, 1.0f,  // Top-left
                1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right
                0.0f, 0.0f, 0.0f, 0.0f,  // Bottom-left

                0.0f, 1.0f, 0.0f, 1.0f,  // Top-left
                1.0f, 1.0f, 1.0f, 1.0f,  // Top-right
                1.0f, 0.0f, 1.0f, 0.0f   // Bottom-right
            };

            glGenVertexArrays(1, &this->quadVAO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

	};
}


#endif // !POLYGON_SPRITE_RENDERER_NODE_HPP
