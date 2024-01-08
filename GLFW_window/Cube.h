#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> //for matrix transformation functions

#include "glslprogram.h"
#include "TextureManager.h"

class Cube
{
private:
	GLuint vertexarray;
	GLuint vertexbuffer;
	GLuint indicearray;
	GLuint textureID;
	std::string textureFileName;
	TextureManager * texManager;
	//make a model matrix to transform the triangle
	glm::mat4 modelMatrix;
	//...and an accumulator for rotatation:
	float angle = 0.f;
	GLSLProgram* shader;
public:
	void Draw();
	void Update(float seconds);
	Cube(GLuint * vertexarray, GLuint * vertexbuffer, GLuint * indicearray, GLuint * textureID, std::string textureFileName, TextureManager *texManager, GLSLProgram* shaders);
	~Cube();
	float getAngle();
	glm::mat4 getModelMatrix();
};
