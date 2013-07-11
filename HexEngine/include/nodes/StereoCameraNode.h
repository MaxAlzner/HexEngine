#ifndef _STEREOCAMERANODE_H_
#define _STEREOCAMERANODE_H_
HEX_BEGIN

class StereoCameraNode : public CameraNode
{
public:

	StereoCameraNode();
	~StereoCameraNode();
		
	float eyeBridge;
};

HEX_END
#endif