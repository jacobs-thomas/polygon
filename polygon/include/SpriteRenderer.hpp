#ifndef POLYGON_SPRITE_RENDERER_HPP
#define POLYGON_SPRITE_RENDERER_HPP

#include "shaders/shader.h"
#include "texture2D.hpp"
#include "type_definitions.hpp"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>                   // For vec3 and mat4 types
#include <glm/gtc/matrix_transform.hpp>   // For translate, rotate, scale functions

namespace polygon {

	class SpriteRenderer {
	private:
		// Instance Attribute:
		Shader shader;
		Texture2D texture;
		unsigned int quadVAO;

		// Methods:
		void InitialiseRenderData() {
            // configure VAO/VBO
            unsigned int VBO;
            float vertices[] = {
                // pos      // tex
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f
            };

            glGenVertexArrays(1, &this->quadVAO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindVertexArray(this->quadVAO);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
		}

	public:
		// Constructor:
		SpriteRenderer(Shader& shader, Texture2D& texture): shader(shader), texture(texture) {
            InitialiseRenderData();
		}

		// Destructor:
		~SpriteRenderer() {
            glDeleteVertexArrays(1, &this->quadVAO);
		}

        // Methods:
        void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
        {
            // prepare transformations
            this->shader.Use();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(position, 0.0f));

            model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
            model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

            model = glm::scale(model, glm::vec3(size, 1.0f));

            this->shader.SetMatrix4f("model", model);
            this->shader.SetVector3f("spriteColor", color);

            glActiveTexture(GL_TEXTURE0);
            texture.Bind();

            glBindVertexArray(this->quadVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
	};

}


#endif // !POLYGON_SPRITE_RENDERER_HPP
