
#include "..\include\HexMain.h"

int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv)) 
		HEX::ToggleRunning();
	
	/*MALib::LOG_Message("START SCENE");
	uint entities[8];
	uint i = 0;
	HEX::GenEntities(7, entities);

	HEX::BindEntity(entities[i]);i++;
	HEX::AddShape(HEX::Meshes[6]);
	HEX::AddMaterial(HEX::Textures[4]);
	HEX::AddSkybox();
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 1.0f, -4.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddCamera(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	HEX::AddController();
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 1.0f, 0.0f, -50.0f, 60.0f, 0.0f);
	HEX::AddLight(HEX::LIGHTMODE_DIRECTIONAL, 1.0f, 0.0f, 0.0f, 0.0f);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(2.0f, 2.0f, -3.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddLight(HEX::LIGHTMODE_POINT, 1.0f);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 60.0f);
	HEX::AddShape(HEX::Meshes[5]);
	HEX::AddMaterial(HEX::Textures[0], HEX::Textures[1]);
	HEX::BoundEntity->material->uvRepeat *= MALib::VEC2(8.0f, 4.0f);
	//torus = BoundEntity;
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddShape(HEX::Meshes[0]);
	HEX::AddMaterial(HEX::Textures[0], HEX::Textures[1]);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 0.0f, 0.0f, -90.0f, 0.0f, 0.0f);
	HEX::AddShape(HEX::Meshes[2]);
	HEX::AddMaterial(HEX::Textures[2], HEX::Textures[3]);
	HEX::BoundEntity->material->uvRepeat *= MALib::VEC2(4.0f, 4.0f);
	HEX::BoundEntity->transform->scale(8.0f, 8.0f, 8.0f);*/

	Uint32 FramePing = SDL_GetTicks();
	Uint32 UpdatePing = SDL_GetTicks();
	while (HEX::IsRunning())
	{
		HEX::PollEvents();
		
		Uint32 NewPing = SDL_GetTicks();
		if (NewPing - FramePing > 16)
		{
			HEX::OnFrameUpdate();
			HEX::OnFrameDraw();
			FramePing = NewPing;
		}
		if (NewPing - UpdatePing > 24)
		{
			HEX::OnFixedUpdate();
			UpdatePing = NewPing;
		}
	}
	
	HEX::Unitialize();
	return 0;
}