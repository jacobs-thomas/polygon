#ifndef POLYGON_SCENE_HPP
#define POLYGON_SCENE_HPP


#include "nodes/node.hpp"
#include <box2d/box2d.h>


namespace polygon {

    class Context {
    private:
        // Constants:
        const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, -10.0f);


        // Instance Attributes:
        std::shared_ptr<Node> root = nullptr;
        b2World* boxWorld = nullptr;


    public:
        // Constructors:
        Context(std::shared_ptr<Node> root = nullptr) : root(root) { 
        
            // Initialise a new world definition with the default gravity constant.
            boxWorld = new b2World(DEFAULT_GRAVITY);
        }


        // Methods:
        inline void SetRootNode(std::shared_ptr<Node> node) {

            root = node;
        }

        inline b2World& GetBoxWorld() const {
            assert(boxWorld != nullptr);
            return *boxWorld;
        }

        inline std::shared_ptr<Node> GetRootNode() const {
            return root;
        }

        void OnInitialise() {
            std::shared_ptr<Node> current = root;

            OnInitialiseNode(current);
        }

        void OnInitialiseNode(std::shared_ptr<Node> node) {

            node->OnInitialise(*this);

            for (int i = 0; i < node->features.size(); i++) {
                node->features[i]->OnInitialise(*this);
            }

            for (int i = 0; i < node->children.size(); i++) {
                OnInitialiseNode(node->children[i]);
            }
        }

        void OnTick(const float deltaTime) {
            std::shared_ptr<Node> current = root;

            OnTickNode(root, deltaTime);
            boxWorld->Step(1.0f / 60.0f, 6, 2);
        }

        void OnTickNode(std::shared_ptr<Node> node, const float deltaTime) {

            node->OnTick(*this, deltaTime);

            for (int i = 0; i < node->features.size(); i++) {
                node->features[i]->OnTick(*this, deltaTime);
            }

            for (int i = 0; i < node->children.size(); i++) {
                OnTickNode(node->children[i], deltaTime);
            }
        }
    };

}


#endif // !POLYGON_SCENE_HPP