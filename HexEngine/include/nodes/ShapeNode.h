#ifndef _SHAPENODE_H_
#define _SHAPENODE_H_
HEX_BEGIN

class ShapeNode : public NodeBase
{
public:

	ShapeNode();
	~ShapeNode();

	void initialize(void* data, unsigned count);
	void unitialize();
	void batch();

	GLuint vao;
	GLuint buffer;
	GLsizei count;
};

HEX_END
#endif