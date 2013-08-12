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
	void build();
	void destroy();

	void setColorMap(uint texture);
	void setNormalMap(uint texture);
	void setSpecularMap(uint texture);

	uint colorTexture;
	uint normalTexture;
	uint specularTexture;
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
	bool built;

	static void BuildTexture(GLuint* outID, MALib::SURFACE* texture);
	static void BuildTexture(GLuint* outID, SDL_Surface* texture);
};

HEX_END
#endif