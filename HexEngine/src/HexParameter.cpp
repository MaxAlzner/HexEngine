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
	ControlNode* control = 0;
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
	case PARAMETER_CAMERA_ASPECT_RATIO:
		GET_CAMERANODE;
		camera->aspectRatio = value;
		break;
	case PARAMETER_CAMERA_NEARZ:
		GET_CAMERANODE;
		camera->nearZ = value;
		break;
	case PARAMETER_CAMERA_FARZ:
		GET_CAMERANODE;
		camera->farZ = value;
		break;
		
	case PARAMETER_CONTROL_SENSITIVITY:
		GET_CONTROLNODE;
		control->sensitivity.x = value;
		control->sensitivity.y = value;
		break;
	case PARAMETER_CONTROL_MOVESPEED_X:
		GET_CONTROLNODE;
		control->moveSpeed.x = value;
		break;
	case PARAMETER_CONTROL_MOVESPEED_Y:
		GET_CONTROLNODE;
		control->moveSpeed.y = value;
		break;
	case PARAMETER_CONTROL_RANGE_X:
		GET_CONTROLNODE;
		control->rangeX.x = -value;
		control->rangeX.y = value;
		break;
	case PARAMETER_CONTROL_RANGE_Y:
		GET_CONTROLNODE;
		control->rangeY.x = -value;
		control->rangeY.y = value;
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