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

	void setTranslationX(float v);
	void setTranslationY(float v);
	void setTranslationZ(float v);
	void setRotationX(float v);
	void setRotationY(float v);
	void setRotationZ(float v);
	void setScaleX(float v);
	void setScaleY(float v);
	void setScaleZ(float v);
	void setTranslation(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	
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