#pragma once

#include <string>
#include <vector>

#include "enemy.h"
#include "camera.h"

class Global
{
public:
    static const int screenWidth = 1920;
    static const int screenHeight = 1080;
    static inline std::string currentTypedWord = "";

    static inline glm::vec3 playerPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    static inline Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    static inline int numberOfEnemies = 3;
    static inline std::vector<std::shared_ptr<CreepEnemy>> enemies;
};