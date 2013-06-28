#include "..\include\HexMain.h"

#ifdef _HEX_SHADER_H_
HEX_BEGIN
	
HEX_API MALib::ARRAY<GLint> Attributes;
HEX_API MALib::ARRAY<GLint> Uniforms;
HEX_API GLuint ShaderProgram = 0;
	
HEX_API void InitializeAttributes()
{
	Attributes.resize(5);
	BindAttribute("vertex");
	BindAttribute("uv");
	BindAttribute("normal");
	BindAttribute("tangent");
	BindAttribute("binormal");
}
HEX_API void InitializeUniforms()
{
	Uniforms.resize(16);
	BindUniform("os_to_ws");
	BindUniform("ws_to_cs");
	BindUniform("ws_to_ls");
	BindUniform("projection");
	BindUniform("directionalLight_ws");
	BindUniform("color_map");
	BindUniform("normal_map");
}

HEX_API void SetUniform(HEX_UNIFORM uniform, void* data)
{
	if (data == NULL) return;

	switch (uniform)
	{
	case HEX_UNIFORM_OS_TO_WS:
		glUniformMatrix4fv(Uniforms[0], 1, GL_FALSE, (const GLfloat*)data);
		break;
	case HEX_UNIFORM_WS_TO_CS:
		glUniformMatrix4fv(Uniforms[1], 1, GL_FALSE, (const GLfloat*)data);
		break;
	case HEX_UNIFORM_WS_TO_LS:
		glUniformMatrix4fv(Uniforms[2], 1, GL_FALSE, (const GLfloat*)data);
		break;
	case HEX_UNIFORM_MODELSPACE:
		glUniformMatrix4fv(Uniforms[0], 1, GL_FALSE, (const GLfloat*)data);
		break;
	case HEX_UNIFORM_WORLDSPACE:
		glUniformMatrix4fv(Uniforms[1], 1, GL_FALSE, (const GLfloat*)data);
		break;
	case HEX_UNIFORM_LIGHTSPACE:
		glUniformMatrix4fv(Uniforms[2], 1, GL_FALSE, (const GLfloat*)data);
		break;
	case HEX_UNIFORM_PROJECTION:
		glUniformMatrix4fv(Uniforms[3], 1, GL_FALSE, (const GLfloat*)data);
		break;
		
	case HEX_UNIFORM_DIRECTIONAL_LIGHT:
		glUniform3fv(Uniforms[4], 1, (const GLfloat*)data);
		break;

	default:
		break;
	}
}
HEX_API void SetTextureSlot(HEX_UNIFORM uniform, GLuint texture)
{
	if (texture == 0) return;

	switch (uniform)
	{
	case HEX_UNIFORM_COLOR_MAP:
		glUniform1i(Uniforms[5], 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		//glBindTexture(GL_TEXTURE_2D, 0);
		break;
	case HEX_UNIFORM_NORMAL_MAP:
		glUniform1i(Uniforms[6], 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		//glBindTexture(GL_TEXTURE_2D, 0);
		break;

	default:
		break;
	}
}

HEX_API bool CompileShader(const char* filepath, GLenum type, GLint* outShader)
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
	MALib::FreeTextFile(&file);
	return true;
}
HEX_API bool BuildProgram(const char* vert_filepath, const char* frag_filepath)
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
HEX_API bool BindAttribute(const char* attribute_location)
{
	GLint a = glGetAttribLocation(ShaderProgram, attribute_location);
	Attributes.add(a);
	if (a < 0)
	{
		MALib::LOG_Message("Could not bind attribute.", attribute_location);
		return false;
	}
	return true;
}
HEX_API bool BindUniform(const char* uniform_location)
{
	GLint u = glGetUniformLocation(ShaderProgram, uniform_location);
	Uniforms.add(u);
	if (u < 0)
	{
		MALib::LOG_Message("Could not bind uniform.", uniform_location);
		return false;
	}
	return true;
}
	
HEX_END
#endif