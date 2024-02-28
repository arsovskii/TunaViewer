#include "Image.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "stb_image.h"

Image::Image(std::string filePath)
{
	stbi_set_flip_vertically_on_load(true);
	mData = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mNrChannels, 0);

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
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

void Image::setupImage()
{
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
