#ifndef _SHAPENODE_H_
#define _SHAPENODE_H_
HEX_BEGIN

class ShapeNode : public NodeBase
{
public:

	ShapeNode();
	~ShapeNode();

	void build(void* data, uint count, uint stride, uint attributes);
	void load();
	void unload();
	void destroy();
	void batch();

	GLuint vao;
	GLuint buffer;
	GLsizei count;
};

HEX_END
#endif