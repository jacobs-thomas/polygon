#ifndef POLYGON_RESOURCE_MANAGER
#define POLYGON_RESOURCE_MANAGER


#include <unordered_map>
#include <string>
#include <memory>
#include <WeakReference.h>
#include <exception>
#include <array>
#include "texture2D.hpp"
#include "shaders/shader.h"


namespace polygon {

	class ResourceManager {
    private:
        // Enum:
        enum class ResourceType {
            SPRITE = 0,
            TEXTURE = 1,
            SHADER = 2,
        };

        // Instance Attributes:
        std::array<std::unordered_map<std::string, std::shared_ptr<Resource>>, 3> resources;
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures;


    public:
        // Constructor:
        ResourceManager() {

        }

        // Methods:
        std::weak_ptr<Shader> SetShader(const std::string& key, const char* vertexShaderFilename, const char* fragmentShaderFilename) {
            // Get the unordered_map for shaders.
            std::unordered_map<std::string, std::shared_ptr<Resource>>& textureMap = resources[static_cast<int>(ResourceType::SHADER)];

            // Insert or overwrite the texture resource
            std::pair< std::unordered_map<std::string, std::shared_ptr<Resource>>::iterator, bool> result = textureMap.emplace(key, std::make_shared<Shader>(vertexShaderFilename, fragmentShaderFilename));

            // If the texture already exists, overwrite it
            if (!result.second) {
                result.first->second = std::make_shared<Shader>(vertexShaderFilename, fragmentShaderFilename);
            }

            return std::dynamic_pointer_cast<Shader>(result.first->second);
        }

        std::weak_ptr<Shader> GetShader(const std::string& key) const {

            // Check if the texture exists in the map.
            std::unordered_map<std::string, std::shared_ptr<Resource>>::const_iterator iterator = resources[(int)ResourceType::SHADER].find(key);
            if (iterator == resources[(int)ResourceType::SHADER].end()) {
                throw std::runtime_error("Shader with key '" + key + "' does not exist.");
            }

            // Return the weak pointer to the texture.
            return std::dynamic_pointer_cast<Shader>(iterator->second);
        }

        std::weak_ptr<Texture2D> SetTexture(const std::string& key, const char* filename) {
            // Get the unordered_map for textures.
            std::unordered_map<std::string, std::shared_ptr<Resource>>& textureMap = resources[static_cast<int>(ResourceType::TEXTURE)];

            // Insert or overwrite the texture resource
            std::pair< std::unordered_map<std::string, std::shared_ptr<Resource>>::iterator, bool> result = textureMap.emplace(key, std::make_shared<Texture2D>(filename));

            // If the texture already exists, overwrite it.
            if (!result.second) {
                result.first->second = std::make_shared<Texture2D>(filename);
            }

            return std::dynamic_pointer_cast<Texture2D>(result.first->second);
        }


        std::weak_ptr<Texture2D> GetTexture(const std::string& key) const {

            // Check if the texture exists in the map.
            std::unordered_map<std::string, std::shared_ptr<Resource>>::const_iterator iterator = resources[(int)ResourceType::TEXTURE].find(key);
            if (iterator == resources[(int)ResourceType::TEXTURE].end()) {
                throw std::runtime_error("Texture with key '" + key + "' does not exist.");
            }

            // Return the weak pointer to the texture.
            return std::dynamic_pointer_cast<Texture2D>(iterator->second);
        }
	};
}

#endif // !POLYGON_RESOURCE_MANAGER
