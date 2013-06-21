#include "..\include\HexMain.h"

#ifdef _SHAPENODE_H_
HEX_BEGIN

ShapeNode::ShapeNode()
{
}
ShapeNode::~ShapeNode()
{
}

void ShapeNode::initialize(void* data, unsigned count)
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->buffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer);
	
	this->count = count;
	GLsizeiptr size = this->count * 20 * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glVertexAttribPointer(Attributes[0], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glVertexAttribPointer(Attributes[1], 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(this->count * 4 * sizeof(float)));
	glVertexAttribPointer(Attributes[2], 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(this->count * 8 * sizeof(float)));
	glVertexAttribPointer(Attributes[3], 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(this->count * 12 * sizeof(float)));
	glVertexAttribPointer(Attributes[4], 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(this->count * 16 * sizeof(float)));
	glEnableVertexAttribArray(Attributes[0]);
	glEnableVertexAttribArray(Attributes[1]);
	glEnableVertexAttribArray(Attributes[2]);
	glEnableVertexAttribArray(Attributes[3]);
	glEnableVertexAttribArray(Attributes[4]);
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void ShapeNode::unitialize()
{
}
void ShapeNode::batch()
{
	if (this->count == 0) return;
	
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer);

	//glDrawElements(GL_TRIANGLES, this->count, GL_UNSIGNED_INT, this->indices);
	glDrawArrays(GL_TRIANGLES, 0, this->count);
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

HEX_END
#endif