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
	UNIFORM_PROJECTION                                         = 0x00000007, 
	
	UNIFORM_DIRECTIONAL_LIGHT_VECTOR                           = 0x00000010, 
	UNIFORM_DIRECTIONAL_LIGHT_COLOR                            = 0x00000011, 
	UNIFORM_POINT_LIGHT_POSITION                               = 0x00000020, 
	UNIFORM_POINT_LIGHT_COLOR                                  = 0x00000021, 
	UNIFORM_POINT_LIGHT_FALLOFF                                = 0x00000022, 
	
	UNIFORM_UV_REPEAT                                          = 0x00000100,  
	
	UNIFORM_COLOR_MAP                                          = 0x00010000, 
	UNIFORM_NORMAL_MAP                                         = 0x00020000, 
};

HEX_API extern MALib::ARRAY<GLint> Attributes;
HEX_API extern MALib::ARRAY<GLint> Uniforms;
HEX_API extern GLuint ShaderProgram;

HEX_API extern void InitializeAttributes();
HEX_API extern void InitializeUniforms();

HEX_API extern void SetUniform(UNIFORM uniform, void* data);
HEX_API extern void SetTextureSlot(UNIFORM uniform, GLuint texture);
	
HEX_API extern bool CompileShader(const string filepath, GLenum type, GLint* outShader);
HEX_API extern bool BuildProgram(const string vert_filepath, const string frag_filepath);
HEX_API extern bool BindAttribute(const string attribute_location);
HEX_API extern bool BindUniform(const string uniform_location);
	
HEX_END
#endif