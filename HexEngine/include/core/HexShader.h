#ifndef _HEX_SHADER_H_
#define _HEX_SHADER_H_
HEX_BEGIN

extern MALib::ARRAY<GLint> Uniforms;
extern MALib::ARRAY<GLint> Attributes;
extern GLuint ShaderProgram;
	
extern bool CompileShader(const char* filepath, GLenum type, GLint* outShader);
extern bool BuildProgram(const char* vert_filepath, const char* frag_filepath);
extern bool BindUniforms(const char** uniform_locations, unsigned int size);
extern bool BindAttributes(const char** attribute_locations, unsigned int size);
	
HEX_END
#endif