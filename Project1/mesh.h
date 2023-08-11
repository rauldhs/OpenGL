#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct  Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoords;
};
struct Texture
{
	unsigned int id;
	std::string type;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(unsigned int shader);
private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};