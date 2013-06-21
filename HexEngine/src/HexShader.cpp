#include "..\include\HexMain.h"

#ifdef _HEX_SHADER_H_
HEX_BEGIN
	
MALib::ARRAY<GLint> Uniforms;
MALib::ARRAY<GLint> Attributes;
GLuint ShaderProgram = 0;

bool CompileShader(const char* filepath, GLenum type, GLint* outShader)
{
	MALib::TEXTFILE* file = NULL;
	if (!MALib::ImportTextFile(filepath, &file))
	{
		MALib::LOG_Message("Could not load shader file.", filepath);
		return false;
	}

	GLint compile_status = GL_FALSE;
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, (const char**)&file->data, 0);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (!compile_status)
	{
		GLint log_length = 0;
		char* buffer = new char[256];
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		glGetShaderInfoLog(shader, 256, &log_length, buffer);

		MALib::LOG_Message("Could not compile shader.", filepath);
		MALib::LOG_Message(buffer);

		delete [] buffer;
		return false;
	}

	*outShader = shader;
	MALib::FreeTextFile(file);
	return true;
}
bool BuildProgram(const char* vert_filepath, const char* frag_filepath)
{
	if (vert_filepath == NULL || frag_filepath == NULL) return false;
	
	GLint link_status = GL_FALSE;

	GLint vs, fs;
	if (!CompileShader(vert_filepath, GL_VERTEX_SHADER, &vs) || !CompileShader(frag_filepath, GL_FRAGMENT_SHADER, &fs)) 
		return false;
	
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vs);
	glAttachShader(ShaderProgram, fs);
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &link_status);
	if (!link_status)
	{
		GLint log_length = 0;
		char* buffer = new char[256];
		glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &log_length);
		glGetProgramInfoLog(ShaderProgram, 256, &log_length, buffer);

		MALib::LOG_Message("Could not link shader program.");
		MALib::LOG_Message(buffer);
		
		delete [] buffer;
		return false;
	}

	glUseProgram(ShaderProgram);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return true;
}
bool BindUniforms(const char** uniform_locations, unsigned int size)
{
	if (uniform_locations == NULL || size < 1) return false;

	Uniforms.resize(size);
	for (unsigned i = 0; i < size; i++)
	{
		const char* uniform = *uniform_locations;
		if (uniform == NULL) return false;
		Uniforms.add(glGetUniformLocation(ShaderProgram, uniform));
		uniform_locations++;
	}
	return true;
}
bool BindAttributes(const char** attribute_locations, unsigned int size)
{
	if (attribute_locations == NULL || size < 1) return false;
	
	Attributes.resize(size);
	for (unsigned i = 0; i < size; i++)
	{
		const char* attribute = *attribute_locations;
		if (attribute == NULL) return false;
		Attributes.add(glGetAttribLocation(ShaderProgram, attribute));
		attribute_locations++;
	}
	return true;
}
	
HEX_END
#endif