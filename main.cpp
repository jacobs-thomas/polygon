#include <gl/glew.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include <type_traits>
#include <glm/vec2.hpp>
#include <memory>
#include <vector>
#include <cassert>
#include <map>
#include <typeindex>

#include "polygon/include/game_object.hpp"
#include "polygon/include/nodes/sprite_renderer.hpp"


namespace polygon {

    class Player : public Node2D {
    public:
        Player() : Node2D() {}

        void OnTick(Scene& scene, const float deltaTime) override {
            Node2D::OnTick(scene, deltaTime);

            SetLocalPosition(GetGlobalPosition() + Vector2f(1.0f, 0.0f));

            std::cout << "Player: OnTick(), delta-time = " << deltaTime << std::endl;

            std::cout << GetGlobalPosition().x << std::endl;
        }

        void OnTreeEnter() override {

        }

        void OnTreeExit() override {

        }
    };

}





#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "polygon/include/transform.hpp"
#include "polygon/include/shaders/shader.h"
#include "polygon/include/SpriteRenderer.hpp"

using namespace polygon;


void PrintVector(const Vector2f& vec) {
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}


int main()
{
    // Set OpenGL context settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Default;

    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    // activate the window (ensures the OpenGL context is active)
    window.setActive(true);

    // Initialize GLEW or GLAD if needed
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR: Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // load resources, initialize the OpenGL states, ...
    Shader spriteShader = Shader("polygon/include/shaders/sprite.vert", "polygon/include/shaders/sprite.frag");
    Texture2D texture = Texture2D("Ben.png");

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    spriteShader.Use();
    spriteShader.SetInt("image", 0);
    spriteShader.SetMatrix4f("projection", projection);

    SpriteRenderer* spriteRenderer = new SpriteRenderer(spriteShader, texture);
    SpriteRendererNode spriteNode = SpriteRendererNode(&spriteShader, &texture);
    Scene scene;

    // Initialization
    window.setFramerateLimit(60);  // Optionally limit the frame rate

    // OpenGL Setup
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set background color
    glEnable(GL_DEPTH_TEST);                // Enable depth testing
    glDepthFunc(GL_LESS);                   // Specify depth comparison

    // Main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
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

        // draw your sprite
        //spriteRenderer->DrawSprite(texture, glm::vec2(280.0f, 200.0f), glm::vec2(205.0f, 148.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        
        spriteNode.transform.SetTranslation(Vector2f(200.0f, 200.0f));
        spriteNode.transform.SetRotation(glm::radians(180.0f));
        spriteNode.transform.SetScale(Vector2f(1.0f, 1.0f));

        spriteNode.OnTick(scene, 0.0f);

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
    return 0;
}


/* 


    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...



*/