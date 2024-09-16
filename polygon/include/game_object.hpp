#ifndef POLYGON_GAME_OBJECT_HPP
#define POLYGON_GAME_OBJECT_HPP


#include <typeindex>
#include <map>
#include "scene.hpp"


namespace polygon {

    class GameObject;

    class Behaviour {
    private:
        // Instance Attributes:
        GameObject* gameObject;

    public:
        // Methods:
        GameObject* GetGameObject() const { return gameObject; }
        virtual void OnTick(const float deltaTime) = 0;
        virtual void OnInitialise() = 0;
        const std::type_index GetTypeIndex() const { return std::type_index(typeid(*this)); }

        friend class GameObject;
    };


    class GameObject : Node2D {

    private:
        // Instance Attributes:
        std::vector<std::shared_ptr<Behaviour>> behaviours = std::vector<std::shared_ptr<Behaviour>>();
        std::map<std::type_index, unsigned int> typeToIndex = std::map<std::type_index, unsigned int>();

    public:
        // Methods:
        void OnTick(Scene& scene, const float deltaTime) override {

            for (int i = 0; i < behaviours.size(); i++) {
                behaviours[i]->OnTick(deltaTime);
            }
        }

        std::shared_ptr<Behaviour> AddComponent(const std::shared_ptr<Behaviour> behaviour) {

            std::type_index typeIndex = std::type_index(typeid(*behaviour));
            if (typeToIndex.find(typeIndex) != typeToIndex.end()) {
                return behaviours[typeToIndex[typeIndex]];
            }

            typeToIndex[typeIndex] = behaviours.size();
            behaviours.push_back(behaviour);
            behaviour->gameObject = this;
            return behaviour;
        }

        std::shared_ptr<Behaviour> GetComponent(const std::type_index& typeIndex) {

            if (typeToIndex.find(typeIndex) == typeToIndex.end()) {
                return nullptr;
            }

            return behaviours[typeToIndex[typeIndex]];
        }

        void OnTreeEnter() override {

        }

        void OnTreeExit() override {

        }
    };
}

#endif // !POLYGON_GAME_OBJECT_HPP
