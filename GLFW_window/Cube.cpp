#include "Cube.h"
extern glm::vec3 trianglePosition;
//this macro helps calculate offsets for VBO stuff
//Pass i as the number of bytes for the offset, so be sure to use sizeof() 
//to help calculate bytes accurately.
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void Cube::Draw()
{
	//send the modelMatrix to the shader
	shader->setUniform("modelMatrix", modelMatrix);

	glBindVertexArray(vertexarray);

	//bind the texture
	texManager->BindTexture(textureID);

	// Draw the cube
	glDrawElements(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
}

void Cube::Update(float seconds)
{
	angle += seconds * 2;
	//calculate model matrix 
	modelMatrix = glm::mat4(1.f); //identity matrix
	//note the order of operations here: translate THEN rotate!
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 1.2f, -1.f));
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(1.f, 1.f, 2.f));
}

Cube::~Cube()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indicearray);
	glDeleteVertexArrays(1, &vertexarray);
}
float Cube::getAngle()
{
	return angle;
}
glm::mat4 Cube::getModelMatrix()
{
	return modelMatrix;
}
Cube::Cube(GLuint *vaoID, GLuint *vboID, GLuint *eboID, GLuint *texID, std::string textureFileName, TextureManager *texManager, GLSLProgram* shaders)
{
	//Assign values of local variables to parameters received
	shader = shaders;
	vertexarray = *vaoID;
	*texID = texManager->LoadTexture(textureFileName);
	textureID = *texID;
	this->texManager = texManager;
	glGenVertexArrays(1, &vertexarray);
	glBindVertexArray(vertexarray);
	// An array of 3 vectors which represents 14 vertices
	GLfloat g_vertex_buffer_data[] =
	{
		//0
		-1.f, 0.0f, 0.0f, //x,y,z
		0.0f, 0.75f,  //u,v
		//1
		-1.f, -1.f, 0.0f,
		0.0f, 0.5f,
		//2
		0.0f, -1.f, 0.0f,
		0.25f, 0.5f,
		//3
		0.0f, 0.0f, 0.0f,
		0.25f, 0.75f,

		//lado 2
		//4
		-1.f, 0.0f, -1.0f, //x,y,z
		0.5f, 1.0f,  //u,v

		//5
		0.0f, 0.0f, -1.0f, //x,y,z
		0.5f, 0.75f,  //u,v

		//6
		0.0f, -1.f, -1.f,
		0.5f, 0.5f,
		//7
		-1.f, -1.f, -1.0f,
		0.5f, 0.25f,
		//8
		-1.f, -1.f, 0.0f,
		0.25f, 0.25f,
		//9
		-1.f, 0.0f, 0.0f,
		0.25f, 1.f,
		//10
		-1.f, -1.f, -1.0f,
		0.75f, 0.5f,
		//11
		-1.f, 0.0f, -1.0f, //x,y,z
		0.75f, 0.75f,
		//12
		-1.f, -1.f, 0.0f,
		1.f, 0.5f,
		//13
		-1.f, 0.0f, 0.0f, //x,y,z
		1.f,0.75f,
	};
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, vboID);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, *vboID);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(GLfloat),  // stride
		(void*)0            // array buffer offset
	);
	glVertexAttribPointer(
		1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(GLfloat),  // stride
		BUFFER_OFFSET(sizeof(GLfloat) * 3)            // array buffer offset
	);
	glEnableVertexAttribArray(0); //channel 0
	glEnableVertexAttribArray(1); //channel 1

	//indices
	GLushort g_indice_buffer_data[] =
	{
		//lado1 bien
		1,2,0, //first triangle
		3,		//second triangle - just need one more vert, it will
		//re-use points 2 and 0 and reverse the winding order

		0xFFFF,		//primitive restart code.
		//lado2
		9,3,4,
		5,

		0xFFFF,
		//lado3 bien
		2,6,3,
		5,

		0xFFFF,		//primitive restart code.
		//lado 4
		7,6,8,
		2,

		0xFFFF,
		//lado 5
		6,10,5,
		11,

		0xFFFF,
		//lado6
		10,12,11,
		13
	};
	// Generate 1 buffer, put the resulting identifier in indexbuffer
	glGenBuffers(1, eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indice_buffer_data), g_indice_buffer_data, GL_STATIC_DRAW);

	glBindVertexArray(0); // Disable our Vertex Array Object? 

	glBindBuffer(GL_ARRAY_BUFFER, 0);// Disable our Vertex Buffer Object

	return;
}