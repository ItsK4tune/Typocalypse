#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Shader;
class CreepEnemy;

std::shared_ptr<CreepEnemy> initCreep(const std::string &word, const Shader &shader);
void initEnemyPool(const std::vector<std::string>& wordList, const Shader& shader);
void trySpawnOneEnemy(const glm::vec3& playerPos);
void spawnInitialEnemies(int n, const glm::vec3& playerPos);
