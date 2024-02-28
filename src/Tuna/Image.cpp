#include "Image.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "stb_image.h"

Image::Image(std::string filePath, GLFWwindow* window)
{
	stbi_set_flip_vertically_on_load(true);
	mData = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mNrChannels, 0);
	mWindow = window;

	if (!mData)
	{
		std::cout << "Failed to load image" << std::endl;
	}
	setup_shader();
	setupImage();
}

Image::~Image()
{
	delete shader;
}

void Image::drawImage()

{

	shader->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Image::setup_texture()
{
	glGenTextures(1, &mTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (mData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(mData);
}

void Image::generate_buffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
}

void Image::setup_shader()
{
	shader = new Shader("src/Tuna/shaders/ImageVertex.vs", "src/Tuna/shaders/ImageFrag.fs");
}

void Image::rescale_image()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	// Calculate 80% of the original monitor's width and height
	int max_width = static_cast<int>(0.8f * mode->width);
	int max_height = static_cast<int>(0.8f * mode->height);

	float scale = 1;
	// Check if the image's width or height is larger than 80% of the monitor's width or height
	if (mWidth > max_width || mHeight > max_height)
	{
		// Calculate the scale factor to fit the image within 80% of the monitor
		scale = std::min(static_cast<float>(max_width) / mWidth, static_cast<float>(max_height) / mHeight);
	
		// Scale the image's width and height
	}


	glfwSetWindowSize(mWindow, mWidth*scale, mHeight*scale);
	glViewport(0, 0, mWidth * scale, mHeight * scale);
}

void Image::setupImage()
{
	
	rescale_image(); 

	setup_texture();

	for (int i = 0; i < 20; i += 5)
	{
		glm::vec3 position(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		glm::vec2 texturePosition(mVertices[i + 3], mVertices[i + 4]);
		Vertex vertex;
		vertex.Position = position;
		vertex.TexCoords = texturePosition;
		vertices.push_back(vertex);
	}

	generate_buffers();


	std::cout << "Image has been loaded" << std::endl;
}
