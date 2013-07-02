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

	void setColorMap(MALib::SURFACE* texture);
	void setColorMap(SDL_Surface* texture);
	void setNormalMap(MALib::SURFACE* texture);
	void setNormalMap(SDL_Surface* texture);

	GLuint colorMap;
	GLuint normalMap;
	MALib::COLOR overlay;
	MALib::COLOR specular;
	float roughness;
	float refIndex;
	MALib::VEC2 uvRepeat;

	static void BuildTexture(GLuint* outID, MALib::SURFACE* texture);
	static void BuildTexture(GLuint* outID, SDL_Surface* texture);
};

HEX_END
#endif