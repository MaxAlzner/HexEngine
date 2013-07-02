#ifndef _SHAPENODE_H_
#define _SHAPENODE_H_
HEX_BEGIN

class HEX_API ShapeNode : public NodeBase
{
public:

	ShapeNode();
	~ShapeNode();

	void build(void* data, uint count, uint stride, uint attributes);
	void load();
	void destroy();
	void batch();

	GLuint vao;
	GLuint buffer;
	GLsizei count;
};

HEX_END
#endif