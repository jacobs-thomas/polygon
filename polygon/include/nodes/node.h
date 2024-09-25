#ifndef POLYGON_NODE_H
#define POLYGON_NODE_H

// Includes.
#include <iostream>
#include <vector>
#include <assert.h>
#include <type_traits>
#include <glm/vec2.hpp>
#include <memory>
#include <vector>
#include <cassert>
#include "../features/feature.h"

#include "../transform.h"

namespace polygon {

    // Forward Declarations.
    class Context;
    class Node;

    // Concepts.
    template<class T>
    concept IsNode = std::is_base_of<Node, T>::value;

    template<class T>
    concept IsFeature = std::is_base_of<Feature, T>::value;

	class Node
	{
    private:
        // Instance Fields:
        Node* parent = nullptr;
        std::vector<std::shared_ptr<Node>> children;
        std::vector<std::shared_ptr<Feature>> features;
        Transform localTransform;
        Transform globalTransform;
        bool isTransformDirty = true;


    public:
        // Methods:
        const Vector2f GetGlobalTranslation();
        void AddChild(const std::shared_ptr<Node>& node);
        const Transform& GetGlobalTransform();
        void SetGlobalTranslation(const Vector2f& translation);

        template<IsFeature T>
        std::weak_ptr<T> AddFeature() {

            for (int i = 0; i < features.size(); i++) {

                std::shared_ptr<T> feature = std::dynamic_pointer_cast<T>(features[i]);

                if (feature) {
                    return feature;
                }
            }

            // Create the shared_ptr for the new feature.
            std::shared_ptr<T> feature = std::make_shared<T>();

            // Set the possessor (the owner node) on the feature.
            feature->possessor = this;

            // Add the feature to the features vector.
            features.push_back(feature);

            // Return a weak_ptr to the feature.
            return feature;
        }

        template <IsFeature T>
        std::weak_ptr<T> GetFeature() {

            for (int i = 0; i < features.size(); i++) {

                std::shared_ptr<T> feature = std::dynamic_pointer_cast<T>(features[i]);

                if (feature) {
                    return feature;
                }
            }

            return std::weak_ptr<T>();
        }


        inline const Transform& GetLocalTransform() const {
            return localTransform;
        }

        inline void SetLocalTranslation(const Vector2f& translation) {
            isTransformDirty = (translation != localTransform.translation);
            localTransform.translation = translation;
        }

        inline void SetLocalRotation(float radians) {
            isTransformDirty = (radians != localTransform.rotation);
            localTransform.rotation = radians;
        }

        inline void SetLocalScale(const Vector2f& scale) {
            isTransformDirty = (scale != localTransform.scale);
            localTransform.scale = scale;
        }

        inline Node* GetParent() const {
            return parent; // Convert weak_ptr to shared_ptr when needed
        }
       

        // Constructor:
        Node() : children(std::vector<std::shared_ptr<Node>>()), parent(nullptr) {}

        // Virtual Methods:
        virtual void OnInitialise(Context& scene) {}
        virtual void OnTick(Context& scene, const float deltaTime) {}
        virtual void OnTreeEnter() {}
        virtual void OnTreeExit() {}
        virtual void OnFixedTick(Context& scene, const float deltaTime) { }

        // Destructor:
        virtual ~Node() {
            children.clear();
            parent = nullptr;
        }

        friend class Context;
	};
}

#endif // !POLYGON_NODE_H

