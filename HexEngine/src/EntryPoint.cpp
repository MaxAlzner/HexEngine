
#include "..\include\HexMain.h"

static uint meshes[16];
static uint textures[32];
static uint entities[32];

void Assets()
{
	HEX::RegisterVMP(meshes + 0, "data/SkySphere.vmp");
	HEX::RegisterVMP(meshes + 1, "data/EV_Catwalk.vmp");
	HEX::RegisterVMP(meshes + 2, "data/EV_Landing_Straight.vmp");
	HEX::RegisterVMP(meshes + 3, "data/EV_Platform.vmp");
	HEX::RegisterVMP(meshes + 4, "data/EV_Stairs.vmp");
	HEX::RegisterVMP(meshes + 5, "data/EV_WallStraight.vmp");
	HEX::RegisterVMP(meshes + 6, "data/EV_WallIn.vmp");
	HEX::RegisterVMP(meshes + 7, "data/EV_WallOut.vmp");

	HEX::RegisterBMP(textures +  0, "data/NightSkyBox.bmp");
	HEX::RegisterTGA(textures +  1, "data/EV_Catwalk_D.tga");
	HEX::RegisterTGA(textures +  2, "data/EV_Catwalk_N.tga");
	HEX::RegisterTGA(textures +  3, "data/EV_Catwalk_S.tga");
	HEX::RegisterTGA(textures +  4, "data/EV_Landing_Straight_D.tga");
	HEX::RegisterTGA(textures +  5, "data/EV_Landing_Straight_N.tga");
	HEX::RegisterTGA(textures +  6, "data/EV_Landing_Straight_S.tga");
	HEX::RegisterTGA(textures +  7, "data/EV_Platform_D.tga");
	HEX::RegisterTGA(textures +  8, "data/EV_Platform_N.tga");
	HEX::RegisterTGA(textures +  9, "data/EV_Platform_S.tga");
	HEX::RegisterTGA(textures + 10, "data/EV_Stairs_D.tga");
	HEX::RegisterTGA(textures + 11, "data/EV_Stairs_N.tga");
	HEX::RegisterTGA(textures + 12, "data/EV_Stairs_S.tga");
	HEX::RegisterTGA(textures + 13, "data/EV_WallStraight_D.tga");
	HEX::RegisterTGA(textures + 14, "data/EV_WallStraight_N.tga");
	HEX::RegisterTGA(textures + 15, "data/EV_WallStraight_S.tga");
	HEX::RegisterTGA(textures + 16, "data/EV_WallIn_D.tga");
	HEX::RegisterTGA(textures + 17, "data/EV_WallIn_N.tga");
	HEX::RegisterTGA(textures + 18, "data/EV_WallIn_S.tga");
	HEX::RegisterTGA(textures + 19, "data/EV_WallOut_D.tga");
	HEX::RegisterTGA(textures + 20, "data/EV_WallOut_N.tga");
	HEX::RegisterTGA(textures + 21, "data/EV_WallOut_S.tga");
}
void Build()
{
	uint i = 0;
	HEX::GenEntities(18, entities);

	HEX::BindEntity(entities[i]);i++;
	//HEX::TransformEntity(0.0f, -1.0f, 0.0f);
	HEX::AddSkybox(meshes[0], textures[0]);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 2.4f, -4.0f);
	HEX::AddController();

	HEX::BindEntity(entities[i]);i++;
	HEX::AddCamera(45.0f, 4.0f / 3.0f, 1.0f, 256.0f);
	HEX::ParentEntity(i - 1, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 8.0f, 0.0f, -80.0f, 60.0f, 0.0f);
	HEX::AddDirectionalLight(0.75f, MALib::COLOR());
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 2.0f, 4.0f);
	HEX::AddPointLight(1.0f, MALib::COLOR(1.0f, 0.25f, 0.1f), 1.2f, 0.25f, 0.01f);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 2.0f, -4.0f);
	HEX::AddPointLight(1.0f, MALib::COLOR(0.0f, 1.0f, 0.2f), 0.7f, 0.25f, 0.01f);
	
	/*HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 2.0f, 0.0f);
	HEX::AddPointLight(1.0f, MALib::COLOR(0.1f, 0.25f, 1.0f), 0.7f, 0.2f, 0.2f);
	*/
	HEX::BindEntity(entities[i]);i++;
	HEX::AddShape(meshes[3]);
	HEX::AddMaterial(textures[7], textures[8], textures[9]);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(2.5f, 0.0f, 0.0f);
	HEX::AddShape(meshes[1]);
	HEX::AddMaterial(textures[1], textures[2], textures[3]);
	HEX::ParentEntity(i - 1, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(2.5f, 0.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[4], textures[5], textures[6]);
	HEX::ParentEntity(i - 2, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(8.331f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[4], textures[5], textures[6]);
	HEX::ParentEntity(i - 3, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(-2.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
	HEX::AddShape(meshes[1]);
	HEX::AddMaterial(textures[1], textures[2], textures[3]);
	HEX::ParentEntity(i - 4, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(-2.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[4], textures[5], textures[6]);
	HEX::ParentEntity(i - 5, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(-8.331f, 0.0f, 0.0f);
	HEX::AddShape(meshes[2]);
	HEX::AddMaterial(textures[4], textures[5], textures[6]);
	HEX::ParentEntity(i - 6, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 0.0f, -5.0f, 0.0f, 90.0f, 0.0f);
	HEX::AddShape(meshes[4]);
	HEX::AddMaterial(textures[10], textures[11], textures[12]);
	HEX::ParentEntity(i - 7, i);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 0.0f, 5.0f, 0.0f, 270.0f, 0.0f);
	HEX::AddShape(meshes[4]);
	HEX::AddMaterial(textures[10], textures[11], textures[12]);
	HEX::ParentEntity(i - 8, i);
	
#if 0
	HEX::BindEntity(entities[i]);i++;
	HEX::AddShape(meshes[5]);
	HEX::AddMaterial(textures[13], textures[14], textures[15]);
	
	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f);
	HEX::AddShape(meshes[5]);
	HEX::AddMaterial(textures[13], textures[14], textures[15]);
#endif

	HEX::BindEntity(entities[i]);i++;
	HEX::TransformEntity(0.0f, 4.8f, 0.0f, 0.0f, 90.0f, 0.0f);
	HEX::AddShape(meshes[3]);
	HEX::AddMaterial(textures[7], textures[8], textures[9]);
	HEX::SetParameter(HEX::PARAMETER_TRANSFORM_SCALE_XYZ, 0.2f, 0.2f, 0.2f);
	HEX::SetParameter(HEX::PARAMETER_MATERIAL_SHADOW_CASTER, true);
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