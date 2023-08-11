#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
std::string readShaderFile(const char* filePath)
{
	std::string code;
	std::ifstream shaderFile;
	// Ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open the file
		shaderFile.open(filePath);
		std::stringstream shaderStream;
		// Read file's buffer contents into the stream
		shaderStream << shaderFile.rdbuf();
		// Close the file handler
		shaderFile.close();
		// Convert stream into a string
		code = shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "Error: Unable to read shader file: " << filePath << std::endl;
	}

	// Return the string directly
	return code;
}

std::string vertexShaderSourceFile = readShaderFile("VertexShader.glsl");
const char*	vertexShaderSource = vertexShaderSourceFile.c_str();

std::string fragmentShaderSourceFile = readShaderFile("CubeFragmentShader.glsl");
const char* fragmentShaderSource = fragmentShaderSourceFile.c_str();

std::string lightFragmentShaderSourceFile = readShaderFile("LightFragmentShader.glsl");
const char* lightFragmentShaderSource = lightFragmentShaderSourceFile.c_str();
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

int WIDTH = 1280, HEIGHT = 720;//resolution
float FOV = 45.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f, pitch = 0.0f;
float lastXPos = WIDTH/2, lastYPos = HEIGHT/2;
float sensitivity = 0.1f;
bool First = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (First)
	{
		lastXPos = xpos;
		lastYPos = ypos;
		First = false;
	}
	float xOffSet = xpos - lastXPos;
	float yOffSet = lastYPos - ypos;
	lastXPos = xpos;
	lastYPos = ypos;
	xOffSet *= sensitivity;
	yOffSet *= sensitivity;
	yaw += xOffSet;
	pitch += yOffSet;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}
int main()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed!" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "idk", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	if (!gladLoadGL())
	{
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(VertexShader);

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(FragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
		std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
		glfwTerminate();
		return -1;
	}

	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
		glfwTerminate();
		return -1;
	}

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
		std::cerr << "Shader program linking failed: " << infoLog << std::endl;
		glfwTerminate();
		return -1;
	}
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int diffuseMap;
	glGenTextures(1, &diffuseMap);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container2.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glUseProgram(ShaderProgram);
	glUniform1i(glGetUniformLocation(ShaderProgram, "material.diffuse"), 0);

	unsigned int specularMap;
	glGenTextures(1, &specularMap);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("container2_specular.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glUseProgram(ShaderProgram);
	glUniform1i(glGetUniformLocation(ShaderProgram, "material.specular"), 1);

	glm::mat4 model = glm::mat4(1);
	glm::mat4 view = glm::mat4(1);
	glm::mat4 proj = glm::mat4(1);

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	glEnable(GL_DEPTH_TEST);
	float deltaTime,lastFrame = 0,cameraSpeed;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		deltaTime = glfwGetTime() - lastFrame;
		cameraSpeed = 2.5f * deltaTime;
		lastFrame = glfwGetTime();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			cameraPos += cameraFront * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			cameraPos -= cameraFront * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			cameraPos -=glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		proj = glm::perspective(FOV, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);

		glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.direction"),1,glm::value_ptr(glm::vec3(-0.2f, -1.0f, -0.3f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.ambient"), 1, glm::value_ptr(glm::vec3(0.05f, 0.05f, 0.05f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		// point light 1
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[0].position"),1,glm::value_ptr(pointLightPositions[0]));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[0].ambient"), 1, glm::value_ptr(glm::vec3(0.05f, 0.05f, 0.05f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[0].diffuse"), 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[0].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[0].quadratic"), 0.032f);
		// point light 2
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[1].position"), 1, glm::value_ptr(pointLightPositions[1]));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[1].ambient"), 1, glm::value_ptr(glm::vec3(0.05f, 0.05f, 0.05f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[1].diffuse"), 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[1].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[1].quadratic"), 0.032f);
		// point light 3
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[2].position"), 1, glm::value_ptr(pointLightPositions[2]));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[2].ambient"), 1, glm::value_ptr(glm::vec3(0.05f, 0.05f, 0.05f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[2].diffuse"), 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[2].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[2].quadratic"), 0.032f);
		// point light 4
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[3].position"), 1, glm::value_ptr(pointLightPositions[3]));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[3].ambient"), 1, glm::value_ptr(glm::vec3(0.05f, 0.05f, 0.05f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[3].diffuse"), 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "pointLights[3].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(ShaderProgram, "pointLights[3].quadratic"), 0.032f);

		glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glUniform3fv(glGetUniformLocation(ShaderProgram, "viewPos"), 1, glm::value_ptr(cameraPos));
		glUniform1f(glGetUniformLocation(ShaderProgram, "material.shininess"), 3200);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

			glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(ShaderProgram);
	glfwTerminate();
}