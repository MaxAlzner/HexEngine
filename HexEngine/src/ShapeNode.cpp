#include "..\include\HexMain.h"

#ifdef _SHAPENODE_H_
HEX_BEGIN

ShapeNode::ShapeNode()
{
	this->type = COMPONENT_SHAPE;

	this->mesh = 0;
	this->vao = 0;
	this->buffer = 0;
	this->count = 0;

	this->built = false;
}
ShapeNode::~ShapeNode()
{
}

void ShapeNode::load()
{
	if (this->root == NULL) return;
	if (this->root->transform == NULL) return;

	SetUniform(UNIFORM_OS_TO_WS, glm::value_ptr(this->root->transform->transformation));
}
void ShapeNode::unload()
{
}
void ShapeNode::build()
{
	MALib::VERTEXBUFFER* vertBuffer = GetMesh(this->mesh);

	if (vertBuffer == 0) return;
	GLsizei count = vertBuffer->vertices;
	uint stride = vertBuffer->stride;
	uint attributes = vertBuffer->components;
	void* data = vertBuffer->buffer;

	this->count = count;
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->buffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	
	GLsizeiptr size = this->count * 20 * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid*)(this->count * 4 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid*)(this->count * 8 * sizeof(float)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid*)(this->count * 12 * sizeof(float)));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid*)(this->count * 16 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->built = true;
}
void ShapeNode::destroy()
{
	if (this->vao != 0) glDeleteVertexArrays(1, &this->vao);
	if (this->buffer != 0) glDeleteBuffers(1, &this->buffer);
	this->count = 0;
	this->built = false;
}
void ShapeNode::batch()
{
	if (this->count == 0 || !this->built) return;
	
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);

	glDrawArrays(GL_TRIANGLES, 0, this->count);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ShapeNode::setMesh(uint mesh)
{
	this->mesh = mesh;
}

HEX_END
#endif