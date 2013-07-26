#include "..\include\HexMain.h"

#ifdef _HEX_PARAMETER_H_
HEX_BEGIN
	
HEX_API void SetParameter(PARAMETER parameter, float value)
{
	if (BoundEntity == NULL) return;

	switch (parameter)
	{
	case PARAMETER_TRANSFORM_TRANSLATION_X:
		BoundEntity->transform->translation.x = value;
		break;
	case PARAMETER_TRANSFORM_TRANSLATION_Y:
		BoundEntity->transform->translation.y = value;
		break;
	case PARAMETER_TRANSFORM_TRANSLATION_Z:
		BoundEntity->transform->translation.z = value;
		break;
	case PARAMETER_TRANSFORM_ROTATION_X:
		BoundEntity->transform->rotation.x = MALib::Module(value, 360.0f);
		break;
	case PARAMETER_TRANSFORM_ROTATION_Y:
		BoundEntity->transform->rotation.y = MALib::Module(value, 360.0f);
		break;
	case PARAMETER_TRANSFORM_ROTATION_Z:
		BoundEntity->transform->rotation.z = MALib::Module(value, 360.0f);
		break;
	case PARAMETER_TRANSFORM_SCALE_X:
		BoundEntity->transform->scaled.x = value;
		break;
	case PARAMETER_TRANSFORM_SCALE_Y:
		BoundEntity->transform->scaled.y = value;
		break;
	case PARAMETER_TRANSFORM_SCALE_Z:
		BoundEntity->transform->scaled.z = value;
		break;
		
	case PARAMETER_MATERIAL_OVERLAY_R:
		BoundEntity->material->overlay.r = value;
		break;
	case PARAMETER_MATERIAL_OVERLAY_G:
		BoundEntity->material->overlay.g = value;
		break;
	case PARAMETER_MATERIAL_OVERLAY_B:
		BoundEntity->material->overlay.b = value;
		break;
	case PARAMETER_MATERIAL_SPECULAR_R:
		BoundEntity->material->specular.r = value;
		break;
	case PARAMETER_MATERIAL_SPECULAR_G:
		BoundEntity->material->specular.g = value;
		break;
	case PARAMETER_MATERIAL_SPECULAR_B:
		BoundEntity->material->specular.b = value;
		break;
	case PARAMETER_MATERIAL_ROUGHNESS:
		BoundEntity->material->roughness = value;
		break;
	case PARAMETER_MATERIAL_REFRACTION_INDEX:
		BoundEntity->material->refIndex = value;
		break;
	case PARAMETER_MATERIAL_UV_REPEAT_U:
		BoundEntity->material->uvRepeat.x = value;
		break;
	case PARAMETER_MATERIAL_UV_REPEAT_V:
		BoundEntity->material->uvRepeat.y = value;
		break;
	case PARAMETER_MATERIAL_UV_OFFSET_U:
		BoundEntity->material->uvOffset.x = value;
		break;
	case PARAMETER_MATERIAL_UV_OFFSET_V:
		BoundEntity->material->uvOffset.y = value;
		break;

	default:
		break;
	}
}
HEX_API void SetParameter(PARAMETER parameter, float v0, float v1, float v2)
{
	if (BoundEntity == NULL) return;

	switch (parameter)
	{
	case PARAMETER_TRANSFORM_TRANSLATION_XYZ:
		BoundEntity->transform->translation.x = v0;
		BoundEntity->transform->translation.y = v1;
		BoundEntity->transform->translation.z = v2;
		break;
	case PARAMETER_TRANSFORM_ROTATION_XYZ:
		BoundEntity->transform->rotation.x = v0;
		BoundEntity->transform->rotation.y = v1;
		BoundEntity->transform->rotation.z = v2;
		break;
	case PARAMETER_TRANSFORM_SCALE_XYZ:
		BoundEntity->transform->scaled.x = v0;
		BoundEntity->transform->scaled.y = v1;
		BoundEntity->transform->scaled.z = v2;
		break;

	case PARAMETER_MATERIAL_OVERLAY_RGB:
		BoundEntity->material->overlay.r = v0;
		BoundEntity->material->overlay.g = v1;
		BoundEntity->material->overlay.b = v2;
		break;
	case PARAMETER_MATERIAL_SPECULAR_RGB:
		BoundEntity->material->specular.r = v0;
		BoundEntity->material->specular.g = v1;
		BoundEntity->material->specular.b = v2;
		break;

	case PARAMETER_LIGHT_COLOR_RGB:
		break;
	case PARAMETER_LIGHT_FALLOFF_XYZ:
		break;

	default:
		break;
	}
}
HEX_API void SetParameter(PARAMETER parameter, uint value)
{
}
HEX_API void SetParameter(PARAMETER parameter, bool value)
{
	if (BoundEntity == NULL) return;

	switch (parameter)
	{
	case PARAMETER_MATERIAL_SHADOW_CASTER:
		BoundEntity->material->shadowCaster = value;
		break;

	default:
		break;
	}
}
	
HEX_END
#endif