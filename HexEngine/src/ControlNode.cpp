#include "..\include\HexMain.h"

#ifdef _CONTROLNODE_H_
HEX_BEGIN

ControlNode::ControlNode()
{
}
ControlNode::~ControlNode()
{
}
		
void ControlNode::load()
{
}
void ControlNode::unload()
{
}
void ControlNode::destroy()
{
}
	
void ControlNode::onStart()
{
}
void ControlNode::onFrameUpdate()
{
}
void ControlNode::onFixedUpdate()
{
	glm::vec3 f;
	glm::vec3 r;
	float rx = 0.0f;
	float ry = 0.0f;

	if (Input::controller.connected)
	{
		f = this->root->transform->forward * Input::GetAxis(XBOX_L_STICK_Y) * -1.0f * DeltaTime;
		r = this->root->transform->right   * Input::GetAxis(XBOX_L_STICK_X) * -1.0f * DeltaTime;
		
		rx = Input::GetAxis(XBOX_R_STICK_X) * -1.0f * DeltaTime;
		ry = Input::GetAxis(XBOX_R_STICK_Y) * DeltaTime;
	}
	else
	{
		float forward = 0.0f;
		float side = 0.0f;
		if (Input::IsKeyDown(KEY_UP)    || Input::IsKeyDown(KEY_W)) forward += 1.0f;
		if (Input::IsKeyDown(KEY_DOWN)  || Input::IsKeyDown(KEY_S)) forward -= 1.0f;
		if (Input::IsKeyDown(KEY_LEFT)  || Input::IsKeyDown(KEY_A)) side += 1.0f;
		if (Input::IsKeyDown(KEY_RIGHT) || Input::IsKeyDown(KEY_D)) side -= 1.0f;
		f = this->root->transform->forward * forward * DeltaTime;
		r = this->root->transform->right * side * DeltaTime;

		rx = ((Input::mouse.scalarY * 2.0f) - 1.0f) * -1.0f * DeltaTime;
		ry = ((Input::mouse.scalarX * 2.0f) - 1.0f) * DeltaTime;
		//if (Input::mouse.scalarX < 0.75f && Input::mouse.scalarX > 0.25f) ry = 0.0f;
		//if (Input::mouse.scalarY < 0.75f && Input::mouse.scalarY > 0.25f) rx = 0.0f;
#if 0
		glm::vec3 ray(((Input::mouse.scalarX * 2.0f) - 1.0f), ((Input::mouse.scalarY * 2.0f) - 1.0f), 1.0f);
		ray = glm::normalize(ray);
		ray *= glm::normalize(glm::mul(ray, this->root->transform->spaceNormal));
		rx = ray.x * DeltaTime;
		ry = ray.y * DeltaTime;
#endif
	}

	/*f.y = 0.0f;
	r.y = 0.0f;
	f = glm::normalize(f);
	r = glm::normalize(r);*/

	this->root->transform->translate(f.x + r.x, 0.0f, f.z + r.z);
	this->root->transform->rotate(rx * 60.0f, ry * 60.0f, 0.0f);
}
	
HEX_END
#endif