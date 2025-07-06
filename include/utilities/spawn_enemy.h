#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Shader;
class CreepEnemy;

void initTriangleMesh();
void initEnemyPool(const std::vector<std::string>& wordList, const Shader& shader);

void deleteTriangleMesh();
