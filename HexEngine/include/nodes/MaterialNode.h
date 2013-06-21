#ifndef _MATERIALNODE_H_
#define _MATERIALNODE_H_

namespace CORE
{
	class Material
	{
	public:
		Material();
		~Material();
		
		virtual void initialize();
		virtual void uninitialize();
		virtual void update();
		virtual void load();
		virtual void remove();

		COLOR overlay, specColor;
		float specIntensity, roughness, refIndex;
		SpriteAnimation* animation;
		Entity* root;
	};
}

#endif