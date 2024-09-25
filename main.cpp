#include "polygon/include/polygon.h"
#include "polygon/include/features/features.hpp"
#include "polygon/include/resource_manager.hpp"

using namespace polygon;


int main()
{
    // Set OpenGL context settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Default;

    PolygonEngine engine = PolygonEngine(800, 600, settings);


    // load resources, initialize the OpenGL states, ...
    std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>("polygon/include/shaders/sprite.vert", "polygon/include/shaders/sprite.frag");
    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>("Ben.png");

    spriteShader->Use();
    spriteShader->SetInt("image", 0);
    spriteShader->SetMatrix4f("projection", engine.GetProjection());

    std::shared_ptr<Node> spriteNode = std::make_shared<Node>();

    engine.GetContext().SetRootNode(spriteNode);
    std::weak_ptr<ScriptFeature> scriptFeature = spriteNode->AddFeature<ScriptFeature>();

    if (std::shared_ptr<ScriptFeature> ptr = scriptFeature.lock()) {

        ptr->LoadFile("script.lua");
    }


    std::weak_ptr<Renderable> spriteRenderer = spriteNode->AddFeature<Renderable>();

    Sprite sprite = Sprite(texture);
    
    if (std::shared_ptr<Renderable> rendererPtr = spriteRenderer.lock()) {

        rendererPtr->SetShader(spriteShader);
        rendererPtr->SetSprite(sprite);
    }


    spriteNode->SetGlobalTranslation(Vector2f(200.0f, 400.0f));


    engine.Initialise();


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