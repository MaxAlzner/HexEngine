
#include "..\include\HexMain.h"

static uint meshes[16];
static uint textures[32];
static uint entities[14];

void Assets()
{
	HEX::RegisterVMP(meshes + 0, "data/SkyDome.vmp");
	HEX::RegisterVMP(meshes + 1, "data/EV_Catwalk.vmp");
	HEX::RegisterVMP(meshes + 2, "data/EV_Landing_Straight.vmp");
	HEX::RegisterVMP(meshes + 3, "data/EV_Platform.vmp");
	HEX::RegisterVMP(meshes + 4, "data/EV_Stairs.vmp");

	HEX::RegisterBMP(textures + 0, "data/CloudsSkyBox.bmp");
	HEX::RegisterTGA(textures + 1, "data/EV_Catwalk_D.tga");
	HEX::RegisterTGA(textures + 2, "data/EV_Catwalk_N.tga");
	HEX::RegisterTGA(textures + 3, "data/EV_Landing_Straight_D.tga");
	HEX::RegisterTGA(textures + 4, "data/EV_Landing_Straight_N.tga");
	HEX::RegisterTGA(textures + 5, "data/EV_Platform_D.tga");
	HEX::RegisterTGA(textures + 6, "data/EV_Platform_N.tga");
	HEX::RegisterTGA(textures + 7, "data/EV_Stairs_D.tga");
	HEX::RegisterTGA(textures + 8, "data/EV_Stairs_N.tga");
}
void Build()
{
	uint i = 0;
	HEX::GenEntities(14, entities);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 1.0f, -4.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddController();

	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddCamera(45.0f, 4.0f / 3.0f, 0.01f, 128.0f);
	HEX::ParentEntity(i - 1, i);

	/*HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(-0.015f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddCamera(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	HEX::ParentEntity(i - 2, i);

	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.015f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddCamera(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	HEX::ParentEntity(i - 3, i);*/
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 8.0f, 0.0f, -80.0f, 60.0f, 0.0f);
	HEX::AddDirectionalLight(0.25f, MALib::COLOR());
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddPointLight(1.0f, MALib::COLOR(), 1.2f, 0.25f, 0.01f);

	HEX::BindEntity(entities[i]);i++;
	//HEX::AddMaterial(textures[0]);
	HEX::AddSkybox(meshes[0], textures[0]);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddShape(meshes[3]);
	HEX::AddMaterial(textures[5], textures[6]);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddShape(meshes[1]);
	HEX::AddMaterial(textures[1], textures[2]);
	HEX::ParentEntity(i - 1, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[3], textures[4]);
	HEX::ParentEntity(i - 2, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(8.331f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[3], textures[4]);
	HEX::ParentEntity(i - 3, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(-2.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
	HEX::AddShape(meshes[1]);
	HEX::AddMaterial(textures[1], textures[2]);
	HEX::ParentEntity(i - 4, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(-2.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[3], textures[4]);
	HEX::ParentEntity(i - 5, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(-8.331f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[3], textures[4]);
	HEX::ParentEntity(i - 6, i);
}

int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv)) 
		HEX::ToggleRunning();

	Assets();
	Build();

	Uint32 FramePing = ~0;//SDL_GetTicks();
	Uint32 UpdatePing = ~0;//SDL_GetTicks();
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