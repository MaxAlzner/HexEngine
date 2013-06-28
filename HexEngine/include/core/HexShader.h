#ifndef _HEX_SHADER_H_
#define _HEX_SHADER_H_
HEX_BEGIN
	
HEX_API typedef enum HEX_UNIFORM
{
	HEX_UNIFORM_NONE                                           = 0x00000000,  
	
	HEX_UNIFORM_OS_TO_WS                                       = 0x00000001, 
	HEX_UNIFORM_WS_TO_CS                                       = 0x00000002, 
	HEX_UNIFORM_WS_TO_LS                                       = 0x00000003, 
	HEX_UNIFORM_MODELSPACE                                     = 0x00000004, 
	HEX_UNIFORM_WORLDSPACE                                     = 0x00000005, 
	HEX_UNIFORM_LIGHTSPACE                                     = 0x00000006, 
	HEX_UNIFORM_PROJECTION                                     = 0x00000007, 
	
	HEX_UNIFORM_DIRECTIONAL_LIGHT                              = 0x00000010, 
	
	HEX_UNIFORM_COLOR_MAP                                      = 0x00010000, 
	HEX_UNIFORM_NORMAL_MAP                                     = 0x00020000, 
};

HEX_API extern MALib::ARRAY<GLint> Attributes;
HEX_API extern MALib::ARRAY<GLint> Uniforms;
HEX_API extern GLuint ShaderProgram;

HEX_API extern void InitializeAttributes();
HEX_API extern void InitializeUniforms();

HEX_API extern void SetUniform(HEX_UNIFORM uniform, void* data);
HEX_API extern void SetTextureSlot(HEX_UNIFORM uniform, GLuint texture);
	
HEX_API extern bool CompileShader(const char* filepath, GLenum type, GLint* outShader);
HEX_API extern bool BuildProgram(const char* vert_filepath, const char* frag_filepath);
HEX_API extern bool BindAttribute(const char* attribute_location);
HEX_API extern bool BindUniform(const char* uniform_location);
	
HEX_END
#endif