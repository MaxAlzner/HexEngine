#include "..\include\HexMain.h"

#ifdef _FIRSTPERSONNODE_H_
HEX_BEGIN

FirstPersonNode::FirstPersonNode()
{
	this->type = COMPONENT_FIRSTPERSON;
	this->rotation = glm::vec2(0.0f, 0.0f);
	this->sensitivity = glm::vec2(30.0f);
	this->moveSpeed = glm::vec2(1.0f);
	this->rangeX = glm::vec2(-360.0f, 360.0f);
	this->rangeY = glm::vec2(-60.0f, 60.0f);
}
FirstPersonNode::~FirstPersonNode()
{
}
		
void FirstPersonNode::load()
{
}
void FirstPersonNode::unload()
{
}
void FirstPersonNode::destroy()
{
}
	
void FirstPersonNode::onStart()
{
	this->rotation.x = this->root->transform->rotation.y;
	//this->rotation.y = this->root->transform->rotation.x;
	SDL_ShowCursor(0);
}
void FirstPersonNode::onFrameUpdate()
{
	glm::vec3 f;
	glm::vec3 r;

	if (Input::controller.connected)
	{
		f = this->root->transform->forward * -Input::GetAxis(XBOX_L_STICK_Y);
		r = this->root->transform->right   * -Input::GetAxis(XBOX_L_STICK_X);
		
		this->rotation.x += Input::GetAxis(XBOX_R_STICK_Y) * this->sensitivity.x * DeltaTime;
		this->rotation.y += Input::GetAxis(XBOX_R_STICK_X) * this->sensitivity.y * DeltaTime;
	}
	else
	{
		float forward = 0.0f;
		float side = 0.0f;
		if (Input::IsKeyDown(KEY_UP)    || Input::IsKeyDown(KEY_W)) forward += 1.0f;
		if (Input::IsKeyDown(KEY_DOWN)  || Input::IsKeyDown(KEY_S)) forward -= 1.0f;
		if (Input::IsKeyDown(KEY_LEFT)  || Input::IsKeyDown(KEY_A)) side += 1.0f;
		if (Input::IsKeyDown(KEY_RIGHT) || Input::IsKeyDown(KEY_D)) side -= 1.0f;
		f = this->root->transform->forward * forward;
		r = this->root->transform->right * side;

		if (Input::mouse.active)
		{
			float mx = ((Input::mouse.scalarX * 2.0f) - 1.0f);
			float my = ((Input::mouse.scalarY * 2.0f) - 1.0f);
			float mag = sqrt(pow(mx, 2) + pow(my, 2));

			this->rotation.x = this->root->transform->rotation.y + (mx * this->sensitivity.x);// * DeltaTime);
			this->rotation.y += my * this->sensitivity.y;// * DeltaTime;
		
			SDL_WarpMouse(ScreenRect.width / 2, ScreenRect.height / 2);
		}
	}

	f *= this->moveSpeed.y * DeltaTime;
	r *= this->moveSpeed.x * DeltaTime;
	this->rotation.y = MALib::Clamp(this->rotation.y, this->rangeY.x, this->rangeY.y);

	this->root->transform->translate(f.x + r.x, 0.0f, f.z + r.z);
	this->root->transform->rotation = glm::vec3(-this->rotation.y, this->rotation.x, 0.0f);
}
void FirstPersonNode::onFixedUpdate()
{
}
	
HEX_END
#endif