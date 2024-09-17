#ifndef POLYGON_RESOURCE_MANAGER
#define POLYGON_RESOURCE_MANAGER


#include <unordered_map>
#include <string>
#include <memory>
#include <WeakReference.h>
#include <exception>
#include "texture2D.hpp"


#define DECLARE_SINGLETON(ClassName) \
public: \
    static ClassName& Singleton() { \
        static ClassName singleton; \
        return singleton; \
    } \
    static ClassName& GetInstance() { return Singleton(); } \


namespace polygon {

	class ResourceManager {
    private:
        // Instance Attributes:
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures;


    public:
        // Methods:
        void SetTexture(const std::string& key, const Texture2D& texture) {

            // Use emplace to insert if the key does not exist.
            std::pair<std::unordered_map<std::string, std::shared_ptr<Texture2D>>::iterator, bool>  result = textures.emplace(key, std::make_shared<Texture2D>(texture));

            // If the texture already exists, overwrite it.
            if (!result.second) {
                *result.first->second = texture;
            }
        }

        std::weak_ptr<Texture2D> GetTexture(const std::string& key) const {

            // Check if the texture exists in the map.
            std::unordered_map<std::string, std::shared_ptr<Texture2D>>::const_iterator it = textures.find(key);
            if (it == textures.end()) {
                throw std::runtime_error("Texture with key '" + key + "' does not exist.");
            }

            // Return the weak pointer to the texture.
            return it->second;
        }
	};
}


#endif // !POLYGON_RESOURCE_MANAGER
