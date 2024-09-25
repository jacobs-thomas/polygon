#pragma once

#include <memory>

namespace polygon {

	class Context;
	class Node;

	class Feature {
	public:
		// Instance Attributes:
		Node* possessor = nullptr;

	protected:
		// Default Constructor:
		Feature() = default;

	public:
		// Methods:
		virtual void OnTick(Context& scene, const float deltaTime) = 0;
		virtual void OnInitialise(Context& scene) = 0;
		virtual void OnLoad() {}
		virtual ~Feature() = default;

		// Friends:
		friend class Node;
	};
}