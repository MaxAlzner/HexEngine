#ifndef _TRANSFORMNODE_H_
#define _TRANSFORMNODE_H_
HEX_BEGIN

class TransformNode : public NodeBase
{
public:

	TransformNode();
	~TransformNode();
	
	void load();
	void unload();
	void destroy();
	
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
	void zero();

	void recalculate();

	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scaled;

	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;
	glm::vec3 position;

	glm::mat4 space;
	glm::mat3 spaceNormal;
	glm::mat4 transformation;
};

HEX_END
#endif