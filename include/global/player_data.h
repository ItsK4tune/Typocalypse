#include <string>
#include <memory>

#include "glm/glm.hpp"
#include "player/player.h"
#include "utilities/AABB.h"

class PlayerData
{
public:
    std::shared_ptr<Player> player;
    std::string currentTypedWord;

    void init(const Shader &shader);
    void clear();
private:
    std::shared_ptr<std::vector<Vertex>> playerVertices;
    std::shared_ptr<std::vector<GLuint>> playerIndices;

    AABB initCircleMesh();
};