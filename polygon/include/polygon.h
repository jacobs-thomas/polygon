#ifndef POLYGON_POLYGON_ENGINE_H
#define POLYGON_POLYGON_ENGINE_H

#include <gl/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <memory>

#include "scene.hpp"
#include "type_definitions.hpp"
#include "resource_manager.hpp"

namespace polygon {

	class PolygonEngine {
	private:
		// Constants:
		const char* WINDOW_NAME = "Polygon Engine";

		// Instance Fields:
		float windowWidth = 0;
		float windowHeight = 0;
		std::unique_ptr<sf::Window> window;
		Matrix4x4f projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, -1.0f, 1.0f);
		std::unique_ptr<Context> context = nullptr;
		bool isRunning = true;
		ResourceManager resourceManager;
		

	public:
		// Constructors:
		PolygonEngine(float windowWidth, float windowHeight, const sf::ContextSettings& settings) : windowWidth(windowWidth), windowHeight(windowHeight) {

			// Construct the sfml window.
			window = std::make_unique<sf::Window>(sf::VideoMode(windowWidth, windowHeight), WINDOW_NAME, sf::Style::Default, settings);
			
			// Setup the sfml window.
			window->setVerticalSyncEnabled(true);
			window->setActive(true);
			window->setFramerateLimit(60);

			// Initialise glew.
			glewExperimental = GL_TRUE;
			assert(glewInit() == GLEW_OK && "ERROR: Failed to initialize GLEW");

			// Setup OpenGL.
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set background color.
			glEnable(GL_DEPTH_TEST);                // Enable depth testing.
			glDepthFunc(GL_LESS);                   // Specify depth comparison.

			// Construct the context.
			if (context == nullptr) { context = std::make_unique<Context>(); }
		}


		// Methods:
		inline ResourceManager& GetResourceManager() {
			return resourceManager;
		}
		
		Context& GetContext() {
			if (context == nullptr) {
				context = std::make_unique<Context>();
			}

			return *context;
		}

		inline const Matrix4x4f& GetProjection() {
			return projection;
		}

		void Initialise() {

			if (context == nullptr) {
				return;
			}

			// Initialise the context.
			context->OnInitialise();


			// Main loop.
			while (isRunning) {

				// handle events
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						// end the program
						isRunning = false;
					}
					else if (event.type == sf::Event::Resized)
					{
						// adjust the viewport when the window is resized
						glViewport(0, 0, event.size.width, event.size.height);

						// Optionally update projection matrix on resize
					}
				}

				// clear the buffers
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Instigate the onTick method.
				context->OnTick(0.0f);

				// end the current frame (internally swaps the front and back buffers)
				window->display();
			}
		}

		PolygonEngine() = delete;
	};
}

#endif // !POLYGON_POLYGON_ENGINE_H