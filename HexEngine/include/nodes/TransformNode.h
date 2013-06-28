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

	USING_GLM_API glm::vec3 translation;
	USING_GLM_API glm::vec3 rotation;
	USING_GLM_API glm::vec3 scaled;

	USING_GLM_API glm::vec3 right;
	USING_GLM_API glm::vec3 up;
	USING_GLM_API glm::vec3 forward;
};

HEX_END
#endif