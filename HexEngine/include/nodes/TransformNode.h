#ifndef _TRANSFORMNODE_H_
#define _TRANSFORMNODE_H_
HEX_BEGIN

class HEX_API TransformNode : public NodeBase
{
public:

	TransformNode();
	~TransformNode();
	
	void load();
	void destroy();
	
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
	void zero();

	void recalculate();

	USING_GLM_API glm::vec3 translation;
	USING_GLM_API glm::vec3 rotation;
	USING_GLM_API glm::vec3 scaled;

	USING_GLM_API glm::vec3 right;
	USING_GLM_API glm::vec3 up;
	USING_GLM_API glm::vec3 forward;
	USING_GLM_API glm::mat4 space;
	USING_GLM_API glm::mat3 spaceNormal;
	USING_GLM_API glm::mat4 transformation;
};

HEX_END
#endif