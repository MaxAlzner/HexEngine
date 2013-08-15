#include "..\include\HexMain.h"

#ifdef _HEX_PARAMETER_H_
HEX_BEGIN
	
HEX_API void ChangeParameter(PARAMETER parameter, float value)
{
	if (BoundEntity == NULL) return;

	switch (parameter)
	{
	case PARAMETER_TRANSFORM_TRANSLATE_X:
		BoundEntity->transform->translate(value, 0.0f, 0.0f);
		break;
	case PARAMETER_TRANSFORM_TRANSLATE_Y:
		BoundEntity->transform->translate(0.0f, value, 0.0f);
		break;
	case PARAMETER_TRANSFORM_TRANSLATE_Z:
		BoundEntity->transform->translate(0.0f, 0.0f, value);
		break;
	case PARAMETER_TRANSFORM_ROTATE_X:
		BoundEntity->transform->rotate(value, 0.0f, 0.0f);
		break;
	case PARAMETER_TRANSFORM_ROTATE_Y:
		BoundEntity->transform->rotate(0.0f, value, 0.0f);
		break;
	case PARAMETER_TRANSFORM_ROTATE_Z:
		BoundEntity->transform->rotate(0.0f, 0.0f, value);
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
HEX_API void ChangeParameter(PARAMETER parameter, float v0, float v1, float v2)
{
	if (BoundEntity == NULL) return;

	LightNode* node = 0;
	switch (parameter)
	{
	case PARAMETER_TRANSFORM_TRANSLATE_XYZ:
		BoundEntity->transform->translation.x = v0;
		BoundEntity->transform->translation.y = v1;
		BoundEntity->transform->translation.z = v2;
		BoundEntity->transform->translate(v0, v1, v2);
		break;
	case PARAMETER_TRANSFORM_ROTATE_XYZ:
		BoundEntity->transform->rotation.x = v0;
		BoundEntity->transform->rotation.y = v1;
		BoundEntity->transform->rotation.z = v2;
		BoundEntity->transform->rotate(v0, v1, v2);
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
		node = BoundEntity->getComponent<LightNode>();
		break;
	case PARAMETER_LIGHT_FALLOFF_XYZ:
		break;

	default:
		break;
	}
}
HEX_API void ChangeParameter(PARAMETER parameter, uint value)
{
}
HEX_API void ChangeParameter(PARAMETER parameter, bool value)
{
	if (BoundEntity == NULL) return;

	switch (parameter)
	{
	case PARAMETER_STATIC:
		BoundEntity->isStatic = value;
		break;

	case PARAMETER_MATERIAL_SHADOW_CASTER:
		BoundEntity->material->shadowCaster = value;
		if (value) Casters.add(BoundEntity);
		else Casters.remove(BoundEntity);
		break;

	default:
		break;
	}
}
	
HEX_END
#endif