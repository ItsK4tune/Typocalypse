#include "utilities/text_renderer.h"
#include <glad/glad.h>
#include <iostream>

TextRenderer::TextRenderer(int w, int h)
    : screenWidth(w), screenHeight(h), textShader("text.vert", "text.frag")
{
    textShader.use();
    glm::mat4 projection = glm::ortho(0.0f, (float)w, 0.0f, (float)h);
    textShader.setMat4("projection", &projection[0][0]);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextRenderer::~TextRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TextRenderer::load(const std::string &fontPath, unsigned int fontSize)
{
    characters.clear();
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cerr << "Could not init FreeType\n";
        return;
    }

    FT_Face face;
    std::string fullPath = std::string("../../resources/fonts/") + fontPath;
    if (FT_New_Face(ft, fullPath.c_str(), 0, &face))
    {
        std::cerr << "Failed to load font\n";
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 32; c < 128; ++c)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            continue;

        unsigned int tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face->glyph->bitmap.width, face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        characters[c] = {
            tex,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x};
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::renderText(const std::string &text, float x, float y, float scale, const glm::vec3 &color)
{
    textShader.use();
    float red = color.x;
    float green = color.y;
    float blue = color.z;
    textShader.setVec3("textColor", red, green, blue);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (auto c : text)
    {
        const Character &ch = characters[c];
        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;
        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
