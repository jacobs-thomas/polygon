#ifndef POLYGON_PROTOTYPES_HPP
#define POLYGON_PROTOTYPES_HPP


#include "../transform.hpp"
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <concepts>

using namespace polygon;

namespace polygonPrototypes {

    // Forward declaration of classes
    class Context;
    class Node;

    template<typename T>
    concept IsNode = std::is_base_of<Node, T>::value;

    // Class representing a Node with transform and branches
    class Node {
    private:
        std::vector<std::shared_ptr<Node>> branches;  // Children nodes (branches)
    public:
        Transform transform;  // Transform for this node

        friend class Context;  // Allow Context to access private members
    };

    // Generic Node Array to store nodes of type T
    template<IsNode T>
    class NodeArrayGeneric {
    public:
        std::vector<T> nodes;  // Storage for nodes of type T
    };

    // Class for processing nodes
    class Processor {
    public:
        // Called during initialization to fetch node array from context
        virtual void OnInitialise(Context& context) {
        }

        // Called on every tick to process each node
       virtual void OnTick(Context& context, float deltaTime) {

        }
    };


    // Main Context class for managing the system state
    class Context {
    private:
        const Vector2f ORIGIN = Vector2f(0.0f, 0.0f);  // Constant origin vector
        std::shared_ptr<Node> root;  // Root node of the context
        std::vector<std::shared_ptr<Processor>> processors;  // List of processors
        std::unordered_map<std::type_index, std::shared_ptr<void>> nodeArrays;  // Node array storage by type

    public:
        // Set the root node
        void SetRoot(const std::shared_ptr<Node>& node) {
            assert(node != nullptr);
            root = node;
        }

        template<IsNode T>
        void AddNode(T node) {
            
            std::type_index type = std::type_index(typeid(T));

            std::cout << "Type Index: " << type.hash_code() << ", Name: " << typeid(T).name() << std::endl;

            if (nodeArrays.find(type) == nodeArrays.end()) {
                nodeArrays[type] = std::make_shared<NodeArrayGeneric<T>>();
            }

            std::shared_ptr<NodeArrayGeneric<T>> nodeArray = std::static_pointer_cast<NodeArrayGeneric<T>>(nodeArrays[type]);
            nodeArray->nodes.push_back(node);
        }

        // Add a processor to the context
        void AddProcessor(const std::shared_ptr<Processor> processor) {
            processors.push_back(processor);
        }

        void OnInitialise(const float deltaTime) {

            for (int i = 0; i < processors.size(); i++) {
                processors[i]->OnInitialise(*this);
            }
        }

        void OnTick(const float deltaTime) {

            for (int i = 0; i < processors.size(); i++) {
                processors[i]->OnTick(*this, deltaTime);
            }
        }

        // Get a generic node array of type T
        template<IsNode T>
        std::shared_ptr<NodeArrayGeneric<T>> GetNodeArray() {
            std::type_index typeIdx = std::type_index(typeid(T));

            std::cout << "Type Index: " << typeIdx.hash_code() << ", Name: " << typeid(T).name() << std::endl;

            // Check if node array of this type exists, otherwise create and insert it
            auto it = nodeArrays.find(typeIdx);
            if (it == nodeArrays.end()) {
                std::shared_ptr<NodeArrayGeneric<T>> newArray = std::make_shared<NodeArrayGeneric<T>>();
                nodeArrays[typeIdx] = newArray;
                return newArray;
            }

            // Return the node array with appropriate type casting
            return std::static_pointer_cast<NodeArrayGeneric<T>>(nodeArrays[typeIdx]);
        }
    };

    class Sprite : public Node {

    };

    class GraphicsProcessor : public Processor {
    private:
        std::shared_ptr<NodeArrayGeneric<Sprite>> sprites;

    public:
        // Called during initialization to fetch node array from context
        virtual void OnInitialise(Context& context) {

            sprites = context.GetNodeArray<Sprite>();
        }

        // Called on every tick to process each node
        virtual void OnTick(Context& context, float deltaTime) {

            std::cout << "Sprite Processor" << std::endl;

            for (Sprite& sprite : sprites->nodes) {

                std::cout << "Found Sprite: " << sprite.transform.GetTranslation().x << ", " << sprite.transform.GetTranslation().y << std::endl;
            }
        }
    };

    class Rigidbody : public Node {

    };

    class PhysicsProcessor : public Processor {
    private:
        std::shared_ptr<NodeArrayGeneric<Rigidbody>> rigidbodies;

    public:
        // Called during initialization to fetch node array from context
        virtual void OnInitialise(Context& context) {

            rigidbodies = context.GetNodeArray<Rigidbody>();
        }

        // Called on every tick to process each node
        virtual void OnTick(Context& context, float deltaTime) {

            std::cout << "Rigidbody Processor" << std::endl;
        }
    };
}
#endif // !POLYGON_PROTOTYPES_HPP
