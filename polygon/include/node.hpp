#ifndef POLYGON_NODE_HPP
#define POLYGON_NODE_HPP


#include <iostream>
#include <vector>
#include <assert.h>
#include <type_traits>
#include <glm/vec2.hpp>
#include <memory>
#include <vector>
#include <cassert>

#include "transform.hpp"


namespace polygon {

    class Scene;
    class Node;

    template<class T>
    concept IsNode = std::is_base_of<Node, T>::value;

    class Node {
    protected:
        // Instance Attributes:
        // Use a weak_ptr for the parent to avoid cyclic references.
        Node* parent = nullptr;
        std::vector<std::shared_ptr<Node>> children;

    public:
        // Methods:
        Node* GetParent() {
            return parent; // Convert weak_ptr to shared_ptr when needed
        }

        void AddChild(const std::shared_ptr<Node>& node) {
            assert(node != nullptr);

            // If the node already has a parent, notify it that it's exiting the tree
            if (node->parent != nullptr) {
                node->OnTreeExit();
            }

            node->parent = this; // Set this as the parent using weak_ptr
            children.push_back(node);

            node->OnTreeEnter();
        }

        // Constructor:
        Node() : children(std::vector<std::shared_ptr<Node>>()), parent(nullptr) {}

        // Methods:
        virtual void OnInitialise(Scene& scene) {}
        virtual void OnTick(Scene& scene, const float deltaTime) {}
        virtual void OnTreeEnter() {}
        virtual void OnTreeExit() {}

        // Destructor:
        virtual ~Node() {
            children.clear();
            parent = nullptr;
        }

        friend class Scene;
    };

    class Node2D : public Node {
    public:
        // Instance Attributes:
        Transform transform;


        // Constructor:
        Node2D() : Node() {}


        // Methods:
        void OnTick(Scene& scene, const float deltaTime) override {
            Node::OnTick(scene, deltaTime);

            std::cout << "Node2D: OnTick(), delta-time = " << deltaTime << std::endl;
        }

        void OnTreeEnter() override {

        }

        void OnTreeExit() override {

        }

        void SetLocalPosition(const Vector2f& position) {
            transform.SetTranslation(position);
        }

        const Vector2f inline GetLocalPosition() const {
            return transform.GetTranslation();
        }

        const Vector2f GetGlobalPosition() const {
            if (parent == nullptr) { return transform.GetTranslation(); }

            // Attempt to lock the weak pointer to a shared pointer
            Node2D* parent2D = dynamic_cast<Node2D*>(parent);

            // If no parent or parent is not a Node2D, return local position as global
            if (parent2D == nullptr) {
                return transform.GetTranslation();
            }

            // Recursively add parent's global position to this node's local position
            return transform.GetTranslation() + parent2D->GetGlobalPosition();
        }
    };


}

#endif // !POLYGON_NODE_HPP