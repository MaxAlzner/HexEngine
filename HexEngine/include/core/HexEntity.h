#ifndef _HEX_ENTITY_H_
#define _HEX_ENTITY_H_
HEX_BEGIN

class HexEntity
{
public:

	HexEntity();
	~HexEntity();

	void start();
	void frameUpdate();
	void fixedUpdate();
	void render();

	void setTransform(TransformNode* node);
	void setMaterial(MaterialNode* node);
	void setShape(ShapeNode* node);
	void addComponent(ComponentNode* node);

	TransformNode* transform;
	MaterialNode* material;
	ShapeNode* shape;
	MALib::ARRAY<ComponentNode*> components;
};

HEX_END
#endif