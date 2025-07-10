#pragma once

#include <map>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class TextRenderer {
public:
    TextRenderer(int screenWidth, int screenHeight);
    ~TextRenderer();

    const std::map<char, Character>& getCharacters() const { return characters; }

    void load(const std::string& fontPath, unsigned int fontSize);
    void renderText(const std::string& text, float x, float y, float scale, const glm::vec4& color);

private:
    std::map<char, Character> characters;
    unsigned int VAO, VBO;
    std::shared_ptr<Shader> textShader;
    int screenWidth, screenHeight;
};
