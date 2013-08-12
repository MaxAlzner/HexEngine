#ifndef _SHAPENODE_H_
#define _SHAPENODE_H_
HEX_BEGIN

class ShapeNode : public NodeBase
{
public:

	ShapeNode();
	~ShapeNode();

	void load();
	void unload();
	void build();
	void destroy();
	void batch();

	void setMesh(uint mesh);

	uint mesh;
	GLuint vao;
	GLuint buffer;
	GLsizei count;

	bool built;
};

HEX_END
#endif