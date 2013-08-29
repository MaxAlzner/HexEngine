#ifndef _ZOOMNODE_H_
#define _ZOOMNODE_H_
HEX_BEGIN
	
class ZoomNode : public ComponentNode
{
public:

	ZoomNode();
	~ZoomNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	float moveSpeed;
};

HEX_END
#endif