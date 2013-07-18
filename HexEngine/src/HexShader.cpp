#include "..\include\HexMain.h"

#ifdef _HEX_SHADER_H_
HEX_BEGIN

struct UniformLocations
{
	int os_to_ws;
	int ws_to_cs;
	int ws_to_ls;
	int projection;
	int directionalLight_ws;
	int directionalLight_color;
	int pointLight4_ws;
	int pointLight4_color;
	int pointLight4_falloff;
	int numOfPointLights;
	int uv_repeat;
	int uv_offset;
	int shadow_size;
	int random_filter;
	int gamma;
	int leftEye_color;
	int rightEye_color;
	int color_map;
	int normal_map;
	int specular_map;
	int depth_map;
	int shadow_map;
	int leftEye_map;
	int rightEye_map;
	int flag;
};

float pointLight4position_buffer[16];
float pointLight4color_buffer[16];
float pointLight4falloff_buffer[16];
uint numOfPointLights = 0;
UNIFORM LastFlag = UNIFORM_FLAG_NORMAL;
UNIFORM CurrentFlag = UNIFORM_FLAG_NORMAL;

MALib::ARRAY<GLint> Attributes;
UniformLocations Uniforms;
GLuint ShaderProgram = 0;
	
HEX_API void InitializeAttributes()
{
	Attributes.resize(5);
	Attributes.add(glGetAttribLocation(ShaderProgram, "vertex"));
	Attributes.add(glGetAttribLocation(ShaderProgram, "uv"));
	Attributes.add(glGetAttribLocation(ShaderProgram, "normal"));
	Attributes.add(glGetAttribLocation(ShaderProgram, "tangent"));
	Attributes.add(glGetAttribLocation(ShaderProgram, "binormal"));
}
HEX_API void InitializeUniforms()
{
	Uniforms.os_to_ws = glGetUniformLocation(ShaderProgram, "os_to_ws");
	Uniforms.ws_to_cs = glGetUniformLocation(ShaderProgram, "ws_to_cs");
	Uniforms.ws_to_ls = glGetUniformLocation(ShaderProgram, "ws_to_ls");
	Uniforms.projection = glGetUniformLocation(ShaderProgram, "projection");
	Uniforms.directionalLight_ws = glGetUniformLocation(ShaderProgram, "directionalLight_ws");
	Uniforms.directionalLight_color = glGetUniformLocation(ShaderProgram, "directionalLight_color");
	Uniforms.pointLight4_ws = glGetUniformLocation(ShaderProgram, "pointLight4_ws");
	Uniforms.pointLight4_color = glGetUniformLocation(ShaderProgram, "pointLight4_color");
	Uniforms.pointLight4_falloff = glGetUniformLocation(ShaderProgram, "pointLight4_falloff");
	Uniforms.numOfPointLights = glGetUniformLocation(ShaderProgram, "numOfPointLights");
	Uniforms.uv_repeat = glGetUniformLocation(ShaderProgram, "uv_repeat");
	Uniforms.uv_offset = glGetUniformLocation(ShaderProgram, "uv_offset");
	Uniforms.shadow_size = glGetUniformLocation(ShaderProgram, "shadow_size");
	Uniforms.random_filter = glGetUniformLocation(ShaderProgram, "random_filter");
	Uniforms.gamma = glGetUniformLocation(ShaderProgram, "gamma");
	Uniforms.leftEye_color = glGetUniformLocation(ShaderProgram, "leftEye_color");
	Uniforms.rightEye_color = glGetUniformLocation(ShaderProgram, "rightEye_color");
	Uniforms.color_map = glGetUniformLocation(ShaderProgram, "color_map");
	Uniforms.normal_map = glGetUniformLocation(ShaderProgram, "normal_map");
	Uniforms.specular_map = glGetUniformLocation(ShaderProgram, "specular_map");
	Uniforms.depth_map = glGetUniformLocation(ShaderProgram, "depth_map");
	Uniforms.shadow_map = glGetUniformLocation(ShaderProgram, "shadow_map");
	Uniforms.leftEye_map = glGetUniformLocation(ShaderProgram, "leftEye_map");
	Uniforms.rightEye_map = glGetUniformLocation(ShaderProgram, "rightEye_map");
	Uniforms.flag = glGetUniformLocation(ShaderProgram, "flag");
	
	uint filter_size = 36 * 2;
	float* randoms = new float[filter_size];
	for (unsigned i = 0; i < filter_size; i += 2)
	{
		float theta = MALib::RANDOM_Scalar() * 3.14f;
		float r = MALib::RANDOM_Scalar();
		float x = cos(theta) * r;
		float y = sin(theta) * r;
		randoms[i + 0] = x;
		randoms[i + 1] = y;
	}
	SetUniform(UNIFORM_RANDOM_FILTER, filter_size / 2, randoms);
	delete [] randoms;

	CurrentFlag = UNIFORM_FLAG_NORMAL;
}

HEX_API void SetUniform(UNIFORM uniform, void* data)
{
	if (data == NULL) return;

	uint n;
	switch (uniform)
	{
	case UNIFORM_OS_TO_WS:
		glUniformMatrix4fv(Uniforms.os_to_ws, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_WS_TO_CS:
		glUniformMatrix4fv(Uniforms.ws_to_cs, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_WS_TO_LS:
		glUniformMatrix4fv(Uniforms.ws_to_ls, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_WORLDSPACE:
		glUniformMatrix4fv(Uniforms.os_to_ws, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_CAMERASPACE:
		glUniformMatrix4fv(Uniforms.ws_to_cs, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_LIGHTSPACE:
		glUniformMatrix4fv(Uniforms.ws_to_ls, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case UNIFORM_PROJECTION:
		glUniformMatrix4fv(Uniforms.projection, 1, GL_FALSE, (const GLfloat*)data);
		break;
		
	case UNIFORM_DIRECTIONAL_LIGHT_VECTOR:
		glUniform3fv(Uniforms.directionalLight_ws, 1, (const GLfloat*)data);
		break;
	case UNIFORM_DIRECTIONAL_LIGHT_COLOR:
		glUniform4fv(Uniforms.directionalLight_color, 1, (const GLfloat*)data);
		break;
		
	case UNIFORM_POINT_LIGHT_POSITION:
		if (numOfPointLights < 1) break;
		n = numOfPointLights - 0;
		pointLight4position_buffer[(n * 4) + 0] = ((float*)data)[0];
		pointLight4position_buffer[(n * 4) + 1] = ((float*)data)[1];
		pointLight4position_buffer[(n * 4) + 2] = ((float*)data)[2];
		pointLight4position_buffer[(n * 4) + 3] = ((float*)data)[3];
		glUniform4fv(Uniforms.pointLight4_ws, 1, (const GLfloat*)pointLight4position_buffer);
		break;
	case UNIFORM_POINT_LIGHT_COLOR:
		if (numOfPointLights < 1) break;
		n = numOfPointLights - 0;
		pointLight4color_buffer[(n * 4) + 0] = ((float*)data)[0];
		pointLight4color_buffer[(n * 4) + 1] = ((float*)data)[1];
		pointLight4color_buffer[(n * 4) + 2] = ((float*)data)[2];
		pointLight4color_buffer[(n * 4) + 3] = ((float*)data)[3];
		glUniform4fv(Uniforms.pointLight4_color, 1, (const GLfloat*)pointLight4color_buffer);
		break;
	case UNIFORM_POINT_LIGHT_FALLOFF:
		if (numOfPointLights < 1) break;
		n = numOfPointLights - 0;
		pointLight4falloff_buffer[(n * 4) + 0] = ((float*)data)[0];
		pointLight4falloff_buffer[(n * 4) + 1] = ((float*)data)[1];
		pointLight4falloff_buffer[(n * 4) + 2] = ((float*)data)[2];
		pointLight4falloff_buffer[(n * 4) + 3] = ((float*)data)[3];
		glUniform3fv(Uniforms.pointLight4_falloff, 1, (const GLfloat*)pointLight4falloff_buffer);
		break;

	case UNIFORM_UV_REPEAT:
		glUniform2fv(Uniforms.uv_repeat, 1, (const GLfloat*)data);
		break;
	case UNIFORM_UV_OFFSET:
		glUniform2fv(Uniforms.uv_offset, 1, (const GLfloat*)data);
		break;
		
	case UNIFORM_SHADOW_MAP_SIZE:
		glUniform1fv(Uniforms.shadow_size, 1, (const GLfloat*)data);
		break;
	case UNIFORM_GAMMA:
		glUniform1fv(Uniforms.gamma, 1, (const GLfloat*)data);
		break;
	case UNIFORM_LEFT_EYE_COLOR:
		glUniform4fv(Uniforms.leftEye_color, 1, (const GLfloat*)data);
		break;
	case UNIFORM_RIGHT_EYE_COLOR:
		glUniform4fv(Uniforms.rightEye_color, 1, (const GLfloat*)data);
		break;

	default:
		break;
	}
}
HEX_API void SetUniform(UNIFORM uniform, uint stackSize, void* data)
{
	if (stackSize == 0 || data == NULL) return;

	switch (uniform)
	{
	case UNIFORM_RANDOM_FILTER:
		glUniform2fv(Uniforms.random_filter, stackSize, (const GLfloat*)data);
		break;

	default:
		break;
	}
}
HEX_API void SetUniform(UNIFORM uniform, bool value)
{
	switch (uniform)
	{

	default:
		break;
	}
}
HEX_API void SetUniform(UNIFORM uniform)
{
	switch (uniform)
	{
	case UNIFORM_ADD_POINT_LIGHT:
		if (numOfPointLights >= 4)
		{
			numOfPointLights = 4;
			break;
		}
		numOfPointLights++;
		glUniform1i(Uniforms.numOfPointLights, numOfPointLights);
		break;
		
	case UNIFORM_FLAG_NORMAL:
		glUniform1i(Uniforms.flag, 0);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_NORMAL;
		break;
	case UNIFORM_FLAG_SHADOW_RENDER:
		glUniform1i(Uniforms.flag, 1);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_SHADOW_RENDER;
		break;
	case UNIFORM_FLAG_BASECOLOR_RENDER:
		glUniform1i(Uniforms.flag, 2);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_BASECOLOR_RENDER;
		break;
	case UNIFORM_FLAG_BLIT_RENDER:
		glUniform1i(Uniforms.flag, 3);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_BLIT_RENDER;
		break;

	case UNIFORM_FLAG_POSTPROCESS_GUASSIAN:
		glUniform1i(Uniforms.flag, 4);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_POSTPROCESS_GUASSIAN;
		break;
	case UNIFORM_FLAG_POSTPROCESS_BILATERAL_GUASSIAN:
		glUniform1i(Uniforms.flag, 5);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_POSTPROCESS_BILATERAL_GUASSIAN;
		break;

	case UNIFORM_FLAG_POSTPROCESS_AMBIENTOCCLUSION:
		glUniform1i(Uniforms.flag, 6);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_POSTPROCESS_AMBIENTOCCLUSION;
		break;
	case UNIFORM_FLAG_POSTPROCESS_LUMINANCE:
		glUniform1i(Uniforms.flag, 7);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_POSTPROCESS_LUMINANCE;
		break;

	case UNIFORM_FLAG_POSTPROCESS_ANAGLYPHIC_3D:
		glUniform1i(Uniforms.flag, 8);
		LastFlag = CurrentFlag;
		CurrentFlag = UNIFORM_FLAG_POSTPROCESS_ANAGLYPHIC_3D;
		break;

	case UNIFORM_FLAG_PREVIOUS:
		SetUniform(LastFlag);
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
	case UNIFORM_TEXTURE_COLOR_MAP:
		glUniform1i(Uniforms.color_map, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case UNIFORM_TEXTURE_NORMAL_MAP:
		glUniform1i(Uniforms.normal_map, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case UNIFORM_TEXTURE_SPECULAR_MAP:
		glUniform1i(Uniforms.specular_map, 3);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case UNIFORM_TEXTURE_DEPTH_MAP:
		glUniform1i(Uniforms.depth_map, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case UNIFORM_TEXTURE_SHADOW_MAP:
		glUniform1i(Uniforms.shadow_map, 5);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case UNIFORM_TEXTURE_LEFT_EYE_MAP:
		glUniform1i(Uniforms.leftEye_map, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case UNIFORM_TEXTURE_RIGHT_EYE_MAP:
		glUniform1i(Uniforms.rightEye_map, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;

	default:
		break;
	}
}
HEX_API extern void ResetUniforms()
{
	numOfPointLights = 0;
	glUniform1i(Uniforms.numOfPointLights, 0);
	glUniform1i(Uniforms.flag, 0);
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
	
	GLint log_length = 0;
	char* buffer = new char[256];
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	glGetShaderInfoLog(shader, 256, &log_length, buffer);

	MALib::LOG_Message("Compiled shader", filepath);
	if (buffer[0] != '\0') MALib::LOG_Message(buffer);

	delete [] buffer;

	if (!compile_status)
	{
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
	
	glBindAttribLocation(ShaderProgram, 0, "vertex");
	glBindAttribLocation(ShaderProgram, 1, "uv");
	glBindAttribLocation(ShaderProgram, 2, "normal");
	glBindAttribLocation(ShaderProgram, 3, "tangent");
	glBindAttribLocation(ShaderProgram, 4, "binormal");

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
	
HEX_END
#endif