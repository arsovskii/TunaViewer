#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Shader.h"
#include "Window.h"


struct Vertex
{
	// position
	glm::vec3 Position;
	// texCoords
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};


class Image
{
public:
	Image(std::string filePath, GLFWwindow* window);

	~Image();

	void drawImage();

	unsigned int VAO;

	int getWidth()
	{
		return mWidth;
	}
	int getHeight()
	{
		return mHeight;
	}

private:
	int mWidth, mHeight, mNrChannels;

	GLFWwindow* mWindow;

	unsigned int mTexture;
	unsigned int VBO, EBO;

	unsigned char* mData;

	float mVertices[20] = {
		// positions         // texture coords
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left 
	};

	std::vector<unsigned int> mIndices = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

	Shader* shader;

	void setupImage();
	void setup_texture();
	void generate_buffers();
	void setup_shader();
	void rescale_image();
};
