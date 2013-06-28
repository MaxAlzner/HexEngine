#ifndef _MATERIALNODE_H_
#define _MATERIALNODE_H_
HEX_BEGIN

class HEX_API MaterialNode : public NodeBase
{
public:

	MaterialNode();
	~MaterialNode();
		
	void load();
	void destroy();

	void add(MALib::SURFACE* texture);

	GLuint colorMap;
	MALib::COLOR overlay;
	MALib::COLOR specular;
	float roughness;
	float refIndex;
};

HEX_END
#endif