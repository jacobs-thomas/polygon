#include "node.h"

void polygon::Node::SetGlobalTranslation(const Vector2f& translation) {
    if (parent != nullptr) {
        // If the node has a parent transform, we need to translate the node in relation to the parent global translation.
        localTransform.translation = translation - parent->GetGlobalTransform().translation;
        return;
    }

    // Otherwise, the local translation becomes representative of the global translation.
    localTransform.translation = translation;
}

const polygon::Vector2f polygon::Node::GetGlobalTranslation() {
    return GetGlobalTransform().translation;
}

void polygon::Node::AddChild(const std::shared_ptr<Node>& node) {
    assert(node != nullptr);

    // If the node already has a parent, notify it that it's exiting the tree.
    if (node->parent != nullptr) {
        node->OnTreeExit();
    }

    node->parent = this;
    children.push_back(node);

    node->OnTreeEnter();
}

const polygon::Transform& polygon::Node::GetGlobalTransform() {
    // If the global transform is up to date (not dirty), then return the global transform without updating the field.
    if (isTransformDirty == false) {
        return globalTransform;
    }

    globalTransform = localTransform;

    if (parent != nullptr) {
        return globalTransform * parent->GetGlobalTransform();
    }

    return globalTransform;
}