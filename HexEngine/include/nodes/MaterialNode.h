#ifndef _MATERIALNODE_H_
#define _MATERIALNODE_H_
HEX_BEGIN

class MaterialNode : public NodeBase
{
public:

	MaterialNode();
	~MaterialNode();
		
	void load();
	void unload();
	void destroy();

	void setColorMap(MALib::SURFACE* texture);
	void setColorMap(SDL_Surface* texture);
	void setNormalMap(MALib::SURFACE* texture);
	void setNormalMap(SDL_Surface* texture);
	void setSpecularMap(MALib::SURFACE* texture);
	void setSpecularMap(SDL_Surface* texture);

	GLuint colorMap;
	GLuint normalMap;
	GLuint specularMap;
	MALib::COLOR overlay;
	MALib::COLOR specular;
	float roughness;
	float refIndex;
	MALib::VEC2 uvRepeat;
	MALib::VEC2 uvOffset;
	bool shadowCaster;

	static void BuildTexture(GLuint* outID, MALib::SURFACE* texture);
	static void BuildTexture(GLuint* outID, SDL_Surface* texture);
};

HEX_END
#endif