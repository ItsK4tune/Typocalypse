#include <iostream>

#include "global/player_data.h"
#include "resource_manager/resource_manager.h"
#include "utilities/resource_enum.h"

void PlayerData::init()
{
    auto playerModel = std::make_shared<Model>(*ResourceManager::getInstance().getModel(std::to_string(static_cast<int>(ResourceType::Player))));
    playerModel->setShader(ResourceManager::getInstance().getShader(std::to_string(static_cast<int>(ShaderType::Default))));
    player = std::make_shared<Player>(playerModel);
    player->setLocalAABB(playerModel->getAABB());
}

void PlayerData::clear()
{
    playerVertices.reset();
    playerIndices.reset();
}