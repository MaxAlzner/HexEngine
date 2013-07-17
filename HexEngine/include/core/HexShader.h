#ifndef _HEX_SHADER_H_
#define _HEX_SHADER_H_
HEX_BEGIN
	
HEX_API typedef enum UNIFORM
{
	UNIFORM_NONE                                               = 0x00000000, 
	
	UNIFORM_OS_TO_WS                                           = 0x00000001, 
	UNIFORM_WS_TO_CS                                           = 0x00000002, 
	UNIFORM_WS_TO_LS                                           = 0x00000003, 
	UNIFORM_WORLDSPACE                                         = 0x00000004, 
	UNIFORM_CAMERASPACE                                        = 0x00000005, 
	UNIFORM_LIGHTSPACE                                         = 0x00000006, 
	UNIFORM_PROJECTION                                         = 0x00000008, 
	
	UNIFORM_DIRECTIONAL_LIGHT_VECTOR                           = 0x00000010, 
	UNIFORM_DIRECTIONAL_LIGHT_COLOR                            = 0x00000011, 
	UNIFORM_ADD_POINT_LIGHT                                    = 0x00000020, 
	UNIFORM_POINT_LIGHT_POSITION                               = 0x00000021, 
	UNIFORM_POINT_LIGHT_COLOR                                  = 0x00000022, 
	UNIFORM_POINT_LIGHT_FALLOFF                                = 0x00000023, 
	
	UNIFORM_UV_REPEAT                                          = 0x00000100, 
	UNIFORM_UV_OFFSET                                          = 0x00000110, 
	
	UNIFORM_SHADOW_MAP_SIZE                                    = 0x00000200, 
	UNIFORM_RANDOM_FILTER                                      = 0x00000210, 
	UNIFORM_GAMMA                                              = 0x00000211, 
	UNIFORM_LEFT_EYE_COLOR                                     = 0x00000221, 
	UNIFORM_RIGHT_EYE_COLOR                                    = 0x00000222, 
	
	UNIFORM_TEXTURE_COLOR_MAP                                  = 0x00010000, 
	UNIFORM_TEXTURE_NORMAL_MAP                                 = 0x00020000, 
	UNIFORM_TEXTURE_SPECULAR_MAP                               = 0x00030000, 
	UNIFORM_TEXTURE_DEPTH_MAP                                  = 0x00011000, 
	UNIFORM_TEXTURE_SHADOW_MAP                                 = 0x00012000, 
	UNIFORM_TEXTURE_LEFT_EYE_MAP                               = 0x00010100, 
	UNIFORM_TEXTURE_RIGHT_EYE_MAP                              = 0x00010200, 
	
	UNIFORM_FLAG_NORMAL                                        = 0x10000000, 
	UNIFORM_FLAG_SHADOW_RENDER                                 = 0x10000001, 
	UNIFORM_FLAG_BASECOLOR_RENDER                              = 0x10000002, 
	UNIFORM_FLAG_BLIT_RENDER                                   = 0x10000003, 
	UNIFORM_FLAG_POSTPROCESS_GUASSIAN                          = 0x20000001, 
	UNIFORM_FLAG_POSTPROCESS_BILATERAL_GUASSIAN                = 0x20000002, 
	UNIFORM_FLAG_POSTPROCESS_AMBIENTOCCLUSION                  = 0x20000010, 
	UNIFORM_FLAG_POSTPROCESS_LUMINANCE                         = 0x20000020, 
	UNIFORM_FLAG_POSTPROCESS_ANAGLYPHIC_3D                     = 0x20001000, 
	UNIFORM_FLAG_PREVIOUS                                      = 0x11000000, 
};

typedef struct UniformLocations UniformLocations;

extern MALib::ARRAY<GLint> Attributes;
extern UniformLocations Uniforms;
extern GLuint ShaderProgram;

HEX_API extern void InitializeAttributes();
HEX_API extern void InitializeUniforms();

HEX_API extern void SetUniform(UNIFORM uniform, void* data);
HEX_API extern void SetUniform(UNIFORM uniform, uint stackSize, void* data);
HEX_API extern void SetUniform(UNIFORM uniform, bool value);
HEX_API extern void SetUniform(UNIFORM uniform);
HEX_API extern void SetTextureSlot(UNIFORM uniform, GLuint texture);
HEX_API extern void ResetUniforms();
	
HEX_API extern bool CompileShader(const string filepath, GLenum type, GLint* outShader);
HEX_API extern bool BuildProgram(const string vert_filepath, const string frag_filepath);
	
HEX_END
#endif