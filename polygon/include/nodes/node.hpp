#ifndef POLYGON_NODE_HPP
#define POLYGON_NODE_HPP


#include "node.h"


namespace polygon {

    class NodeAllocator {
    private:
        // Store a vector of nodes to manage memory safely
        std::vector<std::shared_ptr<Node>> nodes;
        unsigned int position = 0;

    public:
        // Constructor that preallocates memory
        NodeAllocator(size_t maxNodes) {
            nodes.reserve(maxNodes);
            for (size_t i = 0; i < maxNodes; ++i) {
                nodes.push_back(std::make_shared<Node>());
            }
        }

        // Get a node from the pool
        std::shared_ptr<Node> GetNode() {
            if (position < nodes.size()) {
                return nodes[position++];
            }
            else {
                throw std::runtime_error("No more nodes available!");
            }
        }

        // Reset and release the node (can add more advanced handling)
        void Free(std::shared_ptr<Node>& node) {
            if (node) {
                // Reset node's properties
                node->SetGlobalTranslation(Vector2f(0.0f, 0.0f));
                node->SetLocalTranslation(Vector2f(0.0f, 0.0f));
                node->SetLocalRotation(0.0f);
                node->SetLocalScale(Vector2f(1.0f, 1.0f));
                // Mark as free
                node.reset();  // Release ownership
                if (position > 0) --position;
            }
        }
    };
}

#endif // !POLYGON_NODE_HPP