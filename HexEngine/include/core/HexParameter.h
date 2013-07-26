#ifndef _HEX_PARAMETER_H_
#define _HEX_PARAMETER_H_
HEX_BEGIN
	
HEX_API typedef enum PARAMETER
{
	PARAMETER_NONE                                             = 0x00000000, 

	PARAMETER_TRANSFORM_TRANSLATION_X                          = 0x00000001, 
	PARAMETER_TRANSFORM_TRANSLATION_Y                          = 0x00000002, 
	PARAMETER_TRANSFORM_TRANSLATION_Z                          = 0x00000003, 
	PARAMETER_TRANSFORM_ROTATION_X                             = 0x00000004, 
	PARAMETER_TRANSFORM_ROTATION_Y                             = 0x00000005, 
	PARAMETER_TRANSFORM_ROTATION_Z                             = 0x00000006, 
	PARAMETER_TRANSFORM_SCALE_X                                = 0x00000007, 
	PARAMETER_TRANSFORM_SCALE_Y                                = 0x00000008, 
	PARAMETER_TRANSFORM_SCALE_Z                                = 0x00000009, 
	PARAMETER_TRANSFORM_TRANSLATION_XYZ                        = 0x0000000A, 
	PARAMETER_TRANSFORM_ROTATION_XYZ                           = 0x0000000B, 
	PARAMETER_TRANSFORM_SCALE_XYZ                              = 0x0000000C, 
	
	PARAMETER_MATERIAL_OVERLAY_R                               = 0x00000100, 
	PARAMETER_MATERIAL_OVERLAY_G                               = 0x00000200, 
	PARAMETER_MATERIAL_OVERLAY_B                               = 0x00000300, 
	PARAMETER_MATERIAL_SPECULAR_R                              = 0x00000400, 
	PARAMETER_MATERIAL_SPECULAR_G                              = 0x00000500, 
	PARAMETER_MATERIAL_SPECULAR_B                              = 0x00000600, 
	PARAMETER_MATERIAL_OVERLAY_RGB                             = 0x00000A00, 
	PARAMETER_MATERIAL_SPECULAR_RGB                            = 0x00000B00, 
	PARAMETER_MATERIAL_ROUGHNESS                               = 0x00000700, 
	PARAMETER_MATERIAL_REFRACTION_INDEX                        = 0x00000800, 
	PARAMETER_MATERIAL_UV_REPEAT_U                             = 0x00001000, 
	PARAMETER_MATERIAL_UV_REPEAT_V                             = 0x00002000, 
	PARAMETER_MATERIAL_UV_OFFSET_U                             = 0x00003000, 
	PARAMETER_MATERIAL_UV_OFFSET_V                             = 0x00004000, 
	PARAMETER_MATERIAL_SHADOW_CASTER                           = 0x00010000, 
	
	PARAMETER_LIGHT_INTENSITY                                  = 0x10000001, 
	PARAMETER_LIGHT_COLOR_R                                    = 0x10000002, 
	PARAMETER_LIGHT_COLOR_G                                    = 0x10000003, 
	PARAMETER_LIGHT_COLOR_B                                    = 0x10000004, 
	PARAMETER_LIGHT_FALLOFF_CONSTANT                           = 0x10000005, 
	PARAMETER_LIGHT_FALLOFF_LINEAR                             = 0x10000006, 
	PARAMETER_LIGHT_FALLOFF_QUADRATIC                          = 0x10000007, 
	PARAMETER_LIGHT_COLOR_RGB                                  = 0x1000000A, 
	PARAMETER_LIGHT_FALLOFF_XYZ                                = 0x1000000B, 
	
	PARAMETER_CAMERA_FOV_ANGLE                                 = 0x10000010, 
	PARAMETER_CAMERA_ASPECT_RATION                             = 0x10000020, 
	PARAMETER_CAMERA_NEARZ                                     = 0x10000030, 
	PARAMETER_CAMERA_FARZ                                      = 0x10000040, 
};

HEX_API extern void SetParameter(PARAMETER parameter, float value);
HEX_API extern void SetParameter(PARAMETER parameter, float v0, float v1, float v2);
HEX_API extern void SetParameter(PARAMETER parameter, uint value);
HEX_API extern void SetParameter(PARAMETER parameter, bool value);
	
HEX_END
#endif