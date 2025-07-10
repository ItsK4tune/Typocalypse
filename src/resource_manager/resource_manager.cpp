#include "resource_manager/resource_manager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

ResourceManager &ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadFromFile(const std::string &filePath)
{
    std::string fullPath = "../../resources/" + filePath;

    std::ifstream file(fullPath);
    if (!file)
    {
        std::cerr << "[ResourceManager] Failed to open: " << fullPath << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.starts_with("#model"))
        {
            int modelCount;
            std::istringstream(line.substr(6)) >> modelCount;

            for (int i = 0; i < modelCount; ++i)
            {
                std::string idLine, modelLine;
                std::getline(file, idLine);
                std::getline(file, modelLine);

                std::istringstream idStream(idLine);
                std::string ignore, id;
                idStream >> ignore >> id;

                std::istringstream modelStream(modelLine);
                std::string modelTag, path;
                modelStream >> modelTag >> std::quoted(path);

                models[id] = loadModel(path);
            }
        }
        else if (line.starts_with("#shader"))
        {
            int shaderCount;
            std::istringstream(line.substr(7)) >> shaderCount;

            for (int i = 0; i < shaderCount; ++i)
            {
                std::string idLine, vsLine, fsLine, gsLine;

                std::getline(file, idLine);
                std::getline(file, vsLine);
                std::getline(file, fsLine);
                std::getline(file, gsLine);

                std::string id;
                {
                    std::istringstream ss(idLine);
                    std::string ignore;
                    ss >> ignore >> id;
                }

                std::string vsPath, fsPath, gsPath;
                {
                    std::istringstream ss(vsLine);
                    std::string ignore;
                    ss >> ignore >> std::quoted(vsPath);
                }
                {
                    std::istringstream ss(fsLine);
                    std::string ignore;
                    ss >> ignore >> std::quoted(fsPath);
                }

                if (!gsLine.empty() && gsLine.starts_with("gs"))
                {
                    std::istringstream ss(gsLine);
                    std::string ignore;
                    ss >> ignore >> std::quoted(gsPath);
                }

                shaders[id] = !gsPath.empty() ? loadShader(vsPath, fsPath, gsPath) : loadShader(vsPath, fsPath);
            }
        }
        else if (line.starts_with("#texture"))
        {
            int textureCount;
            std::istringstream(line.substr(8)) >> textureCount;

            for (int i = 0; i < textureCount; ++i)
            {
                std::string idLine, texLine;

                std::getline(file, idLine);
                std::getline(file, texLine);

                std::string id;
                {
                    std::istringstream ss(idLine);
                    std::string ignore;
                    ss >> ignore >> id;
                }

                std::string texPath;
                {
                    std::istringstream ss(texPath);
                    std::string ignore;
                    ss >> ignore >> std::quoted(texPath);
                }

                textures[id] = loadTexture(texPath);
            }
        }
    }
}

std::shared_ptr<Shader> ResourceManager::loadShader(const std::string &vsPath, const std::string &fsPath, const std::string &gsPath)
{
    if (gsPath.empty())
        return std::make_shared<Shader>(vsPath, fsPath);
    else
        return std::make_shared<Shader>(vsPath, fsPath, gsPath);
}

std::shared_ptr<Model> ResourceManager::loadModel(const std::string &path)
{
    return std::make_shared<Model>(path);
}

std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string &path){
    return std::make_shared<Texture>(path);
}

std::shared_ptr<Shader> ResourceManager::getShader(const std::string &id) const
{
    auto it = shaders.find(id);
    return (it != shaders.end()) ? it->second : nullptr;
}

std::shared_ptr<Model> ResourceManager::getModel(const std::string &id) const
{
    auto it = models.find(id);
    return (it != models.end()) ? it->second : nullptr;
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string &id) const
{
    auto it = textures.find(id);
    return (it != textures.end()) ? it->second : nullptr;
}

void ResourceManager::clear()
{
    shaders.clear();
    models.clear();
}