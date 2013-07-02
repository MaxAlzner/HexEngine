#include "..\include\HexMain.h"

#ifdef _HEX_SHADER_H_
HEX_BEGIN
	
HEX_API int UniformLocations_os_to_ws = -1;
HEX_API int UniformLocations_ws_to_cs = -1;
HEX_API int UniformLocations_ws_to_ls = -1;
HEX_API int UniformLocations_projection = -1;
HEX_API int UniformLocations_directionalLight_ws = -1;
HEX_API int UniformLocations_directionalLight_color = -1;
HEX_API int UniformLocations_pointLight4_ws = -1;
HEX_API int UniformLocations_pointLight4_color = -1;
HEX_API int UniformLocations_pointLight4_falloff = -1;
HEX_API int UniformLocations_numOfPointLights = -1;
HEX_API int UniformLocations_uv_repeat = -1;
HEX_API int UniformLocations_color_map = -1;
HEX_API int UniformLocations_normal_map = -1;

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
	UniformLocations_os_to_ws = glGetUniformLocation(ShaderProgram, "os_to_ws");
	UniformLocations_ws_to_cs = glGetUniformLocation(ShaderProgram, "ws_to_cs");
	UniformLocations_ws_to_ls = glGetUniformLocation(ShaderProgram, "ws_to_ls");
	UniformLocations_projection = glGetUniformLocation(ShaderProgram, "projection");
	UniformLocations_directionalLight_ws = glGetUniformLocation(ShaderProgram, "directionalLight_ws");
	UniformLocations_directionalLight_color = glGetUniformLocation(ShaderProgram, "directionalLight_color");
	UniformLocations_pointLight4_ws = glGetUniformLocation(ShaderProgram, "pointLight4_ws");
	UniformLocations_pointLight4_color = glGetUniformLocation(ShaderProgram, "pointLight4_color");
	UniformLocations_pointLight4_falloff = glGetUniformLocation(ShaderProgram, "pointLight4_falloff");
	UniformLocations_numOfPointLights = glGetUniformLocation(ShaderProgram, "numOfPointLights");
	UniformLocations_color_map = glGetUniformLocation(ShaderProgram, "color_map");
	UniformLocations_normal_map = glGetUniformLocation(ShaderProgram, "normal_map");
	UniformLocations_uv_repeat = glGetUniformLocation(ShaderProgram, "uv_repeat");
}

HEX_API void SetUniform(UNIFORM uniform, void* data)
{
	if (data == NULL) return;

	switch (uniform)
	{
	case UNIFORM_OS_TO_WS:
		glUniformMatrix4fv(UniformLocations_os_to_ws, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_WS_TO_CS:
		glUniformMatrix4fv(UniformLocations_ws_to_cs, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_WS_TO_LS:
		glUniformMatrix4fv(UniformLocations_ws_to_ls, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_WORLDSPACE:
		glUniformMatrix4fv(UniformLocations_os_to_ws, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_CAMERASPACE:
		glUniformMatrix4fv(UniformLocations_ws_to_cs, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_LIGHTSPACE:
		glUniformMatrix4fv(UniformLocations_ws_to_ls, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_PROJECTION:
		glUniformMatrix4fv(UniformLocations_projection, 1, GL_FALSE, (const GLfloat*)data);
		break;
		
	case UNIFORM_DIRECTIONAL_LIGHT_VECTOR:
		glUniform3fv(UniformLocations_directionalLight_ws, 1, (const GLfloat*)data);
		break;
	case UNIFORM_DIRECTIONAL_LIGHT_COLOR:
		glUniform4fv(UniformLocations_directionalLight_color, 1, (const GLfloat*)data);
		break;
		
	case UNIFORM_POINT_LIGHT_POSITION:
		glUniform4fv(UniformLocations_pointLight4_ws, 1, (const GLfloat*)data);
		break;
	case UNIFORM_POINT_LIGHT_COLOR:
		glUniform4fv(UniformLocations_pointLight4_color, 1, (const GLfloat*)data);
		break;
	case UNIFORM_POINT_LIGHT_FALLOFF:
		glUniform3fv(UniformLocations_pointLight4_falloff, 1, (const GLfloat*)data);
		break;

	case UNIFORM_UV_REPEAT:
		glUniform2fv(UniformLocations_uv_repeat, 1, (const GLfloat*)data);
		break;

	default:
		break;
	}
}
HEX_API void SetTextureSlot(UNIFORM uniform, GLuint texture)
{
	if (texture == 0) return;

	switch (uniform)
	{
	case UNIFORM_COLOR_MAP:
		glUniform1i(UniformLocations_color_map, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case UNIFORM_NORMAL_MAP:
		glUniform1i(UniformLocations_normal_map, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;

	default:
		break;
	}
}

HEX_API bool CompileShader(const string filepath, GLenum type, GLint* outShader)
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
HEX_API bool BuildProgram(const string vert_filepath, const string frag_filepath)
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
HEX_API bool BindAttribute(const string attribute_location)
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
HEX_API bool BindUniform(const string uniform_location)
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