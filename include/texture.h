#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public: 
    Texture();
	Texture(const std::string& fileName);
	~Texture();
	
    unsigned int GetID() const { return m_ID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
	unsigned char* GetData() const { return m_Data; }

	bool LoadFromFile(const std::string& fileName);
    void BindToUnit(GLuint unit) const;
    void Unbind() const;

private:
    GLuint m_ID;
    int m_Width;
    int m_Height; 
    unsigned char* m_Data;
};	