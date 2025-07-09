#include "model.h"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model()
    : vertices(std::make_shared<std::vector<Vertex>>()), indices(std::make_shared<std::vector<GLuint>>()), shader(nullptr),
      VAO(0), VBO(0), EBO(0)
{
}

Model::Model(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<GLuint>> indices)
    : vertices(vertices), indices(indices), shader(nullptr),
      VAO(0), VBO(0), EBO(0)
{
    initialize();
}

Model::Model(const std::string &filePath)
    : vertices(nullptr), indices(nullptr), shader(nullptr),
      VAO(0), VBO(0), EBO(0)
{
    loadModel(filePath);
    initialize();
}

Model::Model(const Model &other)
{
    if (other.vertices)
        vertices = std::make_shared<std::vector<Vertex>>(*other.vertices);
    if (other.indices)
        indices = std::make_shared<std::vector<GLuint>>(*other.indices);

    shader = other.shader;

    position = other.position;
    rotation = other.rotation;
    scale = other.scale;

    VAO = VBO = EBO = 0;
    initialize();
}

Model::~Model()
{
    cleanup();
}

void Model::loadModel(const std::string &filePath)
{
    std::string fullPath = "../../resources/models/" + filePath;

    std::ifstream file(fullPath);
    if (!file)
    {
        std::cerr << "[Model::loadModel] Failed to open file: " << fullPath << "\n";
        return;
    }

    std::string line;
    size_t vertexCount = 0;
    size_t indexCount = 0;

    vertices = std::make_shared<std::vector<Vertex>>();
    indices = std::make_shared<std::vector<GLuint>>();

    while (std::getline(file, line))
    {
        if (line.starts_with("#vertices"))
        {
            std::istringstream iss(line.substr(9));
            iss >> vertexCount;

            for (size_t i = 0; i < vertexCount; ++i)
            {
                float px, py, pz;
                float r, g, b;

                std::getline(file, line);
                std::istringstream vss(line);
                vss >> px >> py >> pz >> r >> g >> b;

                Vertex v;
                v.position = glm::vec3(px, py, pz);
                v.color = glm::vec3(r, g, b);

                vertices->push_back(v);
            }
        }
        else if (line.starts_with("#indices"))
        {
            std::istringstream iss(line.substr(8));
            iss >> indexCount;

            for (size_t i = 0; i < indexCount; ++i)
            {
                GLuint a, b, c;

                std::getline(file, line);
                std::istringstream issTri(line);
                issTri >> a >> b >> c;

                indices->push_back(a);
                indices->push_back(b);
                indices->push_back(c);
            }
        }
    }

    std::cout << "[Model::loadModel] Loaded " << vertices->size() << " vertices and "
              << indices->size() << " indices from " << fullPath << "\n";
}

void Model::loadVertexData(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<GLuint>> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    initialize();
}

void Model::initialize()
{
    if (!vertices || !indices)
    {
        std::cerr << "[Model::initialize] vertex/index data not valid.\n";
        return;
    }

    GLuint vertexCount = static_cast<unsigned int>(vertices->size());
    GLuint indexCount = static_cast<unsigned int>(indices->size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices->data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, color)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, texCoords)));

    glBindVertexArray(0);
}

void Model::cleanup()
{
    if (EBO)
        glDeleteBuffers(1, &EBO);
    if (VBO)
        glDeleteBuffers(1, &VBO);
    if (VAO)
        glDeleteVertexArrays(1, &VAO);

    EBO = VBO = VAO = 0;
}

void Model::draw()
{
    if (!shader)
    {
        std::cerr << "[Model::draw] Shader not set.\n";
        return;
    }

    GLuint indexCount = static_cast<unsigned int>(indices->size());

    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Model::setShader(std::shared_ptr<Shader> shader)
{
    this->shader = shader;
}

glm::mat4 Model::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
    return model;
}

AABB Model::getAABB() const
{
    if (!vertices || vertices->empty())
    {
        return AABB();
    }

    glm::mat4 modelMatrix = getModelMatrix();
    glm::vec3 minPoint(FLT_MAX);
    glm::vec3 maxPoint(-FLT_MAX);

    for (const auto &v : *vertices)
    {
        glm::vec4 worldPos = modelMatrix * glm::vec4(v.position, 1.0f);
        glm::vec3 pos3 = glm::vec3(worldPos);

        minPoint = glm::min(minPoint, pos3);
        maxPoint = glm::max(maxPoint, pos3);
    }

    return AABB(minPoint, maxPoint);
}