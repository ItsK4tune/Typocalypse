#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "shader.h"
#include "model.h"
#include "texture.h"

class ResourceManager {
public:
    static ResourceManager& getInstance();

    void loadFromFile(const std::string& filePath);

    std::shared_ptr<Shader> getShader(const std::string& id) const;
    std::shared_ptr<Model> getModel(const std::string& id) const;
    std::shared_ptr<Texture> getTexture(const std::string& id) const;

    void clear();

private:
    ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Model>> models;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

    std::shared_ptr<Shader> loadShader(const std::string& vsPath, const std::string& fsPath, const std::string& gsPath = "");
    std::shared_ptr<Model> loadModel(const std::string& path);
    std::shared_ptr<Texture> loadTexture(const std::string& path);
};
