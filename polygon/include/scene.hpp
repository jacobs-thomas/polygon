#ifndef POLYGON_SCENE_HPP
#define POLYGON_SCENE_HPP


#include "node.hpp"


namespace polygon {

    class Scene {
    private:
        // Instance Attributes:
        std::shared_ptr<Node> root = nullptr;


    public:
        // Constructors:
        Scene() : root(std::make_shared<Node>()) { }
        Scene(std::shared_ptr<Node> root) : root(root) { }


        // Methods:
        void OnTick(const float deltaTime) {
            std::shared_ptr<Node> current = root;

            OnTickNode(root, deltaTime);
        }

        void OnTickNode(std::shared_ptr<Node> node, const float deltaTime) {

            node->OnTick(*this, deltaTime);

            for (int i = 0; i < node->children.size(); i++) {
                OnTickNode(node->children[i], deltaTime);
            }
        }
    };

}


#endif // !POLYGON_SCENE_HPP