#include "..\include\HexMain.h"

#ifdef _HEX_PARAMETER_H_
HEX_BEGIN

#define GET_LIGHTODE \
	light = GetComponent<LightNode>();\
	if (light == 0) break;
#define GET_CAMERANODE \
	camera = GetComponent<CameraNode>();\
	if (camera == 0) break;
#define GET_CONTROLNODE \
	control = GetComponent<ControlNode>();\
	if (control == 0) break;
	
HEX_API void ChangeParameter(PARAMETER parameter, float value)
{
	if (BoundEntity == NULL) return;
	
	LightNode* light = 0;
	CameraNode* camera = 0;
	FirstPersonNode* firstPerson = 0;
	ThirdPersonNode* thirdPerson = 0;
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
		
	case PARAMETER_LIGHT_INTENSITY:
		GET_LIGHTODE;
		light->intensity = value;
		break;
	case PARAMETER_LIGHT_COLOR_R:
		GET_LIGHTODE;
		light->color.r = value;
		break;
	case PARAMETER_LIGHT_COLOR_G:
		GET_LIGHTODE;
		light->color.g = value;
		break;
	case PARAMETER_LIGHT_COLOR_B:
		GET_LIGHTODE;
		light->color.b = value;
		break;
	case PARAMETER_LIGHT_FALLOFF_CONSTANT:
		GET_LIGHTODE;
		light->falloff.r = value;
		break;
	case PARAMETER_LIGHT_FALLOFF_LINEAR:
		GET_LIGHTODE;
		light->falloff.y = value;
		break;
	case PARAMETER_LIGHT_FALLOFF_QUADRATIC:
		GET_LIGHTODE;
		light->falloff.z = value;
		break;
		
	case PARAMETER_CAMERA_FOV_ANGLE:
		GET_CAMERANODE;
		camera->fovAngle = value;
		break;
	case PARAMETER_CAMERA_NEARZ:
		GET_CAMERANODE;
		camera->nearZ = value;
		break;
	case PARAMETER_CAMERA_FARZ:
		GET_CAMERANODE;
		camera->farZ = value;
		break;
		
	case PARAMETER_FIRSTPERSON_SENSITIVITY:
		firstPerson = GetComponent<FirstPersonNode>();
		if (firstPerson == 0) break;
		firstPerson->sensitivity.x = value;
		firstPerson->sensitivity.y = value;
		break;
	case PARAMETER_FIRSTPERSON_MOVESPEED_X:
		firstPerson = GetComponent<FirstPersonNode>();
		if (firstPerson == 0) break;
		firstPerson->moveSpeed.x = value;
		break;
	case PARAMETER_FIRSTPERSON_MOVESPEED_Y:
		firstPerson = GetComponent<FirstPersonNode>();
		if (firstPerson == 0) break;
		firstPerson->moveSpeed.y = value;
		break;
	case PARAMETER_FIRSTPERSON_RANGE_X:
		firstPerson = GetComponent<FirstPersonNode>();
		if (firstPerson == 0) break;
		firstPerson->rangeX.x = -value;
		firstPerson->rangeX.y = value;
		break;
	case PARAMETER_FIRSTPERSON_RANGE_Y:
		firstPerson = GetComponent<FirstPersonNode>();
		if (firstPerson == 0) break;
		firstPerson->rangeY.x = -value;
		firstPerson->rangeY.y = value;
		break;
	case PARAMETER_THIRDPERSON_SENSITIVITY:
		thirdPerson = GetComponent<ThirdPersonNode>();
		if (thirdPerson == 0) break;
		thirdPerson->sensitivity.x = value;
		thirdPerson->sensitivity.y = value;
		break;
	case PARAMETER_THIRDPERSON_MOVESPEED_X:
		thirdPerson = GetComponent<ThirdPersonNode>();
		if (thirdPerson == 0) break;
		thirdPerson->moveSpeed.x = value;
		break;
	case PARAMETER_THIRDPERSON_MOVESPEED_Y:
		thirdPerson = GetComponent<ThirdPersonNode>();
		if (thirdPerson == 0) break;
		thirdPerson->moveSpeed.y = value;
		break;

	default:
		break;
	}
}
HEX_API void ChangeParameter(PARAMETER parameter, float v0, float v1, float v2)
{
	if (BoundEntity == NULL) return;

	LightNode* light = 0;
	switch (parameter)
	{
	case PARAMETER_TRANSFORM_TRANSLATE_XYZ:
		BoundEntity->transform->translate(v0, v1, v2);
		break;
	case PARAMETER_TRANSFORM_ROTATE_XYZ:
		BoundEntity->transform->rotate(v0, v1, v2);
		break;
	case PARAMETER_TRANSFORM_SCALE_XYZ:
		BoundEntity->transform->scale(v0, v1, v2);
		break;

	case PARAMETER_MATERIAL_OVERLAY_RGB:
		BoundEntity->material->setOverlay(v0, v1, v2);
		break;
	case PARAMETER_MATERIAL_SPECULAR_RGB:
		BoundEntity->material->setSpecular(v0, v1, v2);
		break;

	case PARAMETER_LIGHT_COLOR_RGB:
		GET_LIGHTODE;
		light->color.r = v0;
		light->color.g = v1;
		light->color.b = v2;
		break;
	case PARAMETER_LIGHT_FALLOFF_XYZ:
		GET_LIGHTODE;
		light->falloff.x = v0;
		light->falloff.y = v1;
		light->falloff.z = v2;
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