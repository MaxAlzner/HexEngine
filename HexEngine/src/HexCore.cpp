#include "..\include\HexMain.h"

#ifdef _HEX_CORE_H_
HEX_BEGIN
	
static const float plane_data[] = 
{
	 1.0,  1.0, 0.0, 1.0, 
	-1.0,  1.0, 0.0, 1.0, 
	 1.0, -1.0, 0.0, 1.0, 
	-1.0,  1.0, 0.0, 1.0, 
	 1.0, -1.0, 0.0, 1.0, 
	-1.0, -1.0, 0.0, 1.0, 

	1.0, 1.0, 0.0, 0.0, 
	0.0, 1.0, 0.0, 0.0, 
	1.0, 0.0, 0.0, 0.0, 
	0.0, 1.0, 0.0, 0.0, 
	1.0, 0.0, 0.0, 0.0, 
	0.0, 0.0, 0.0, 0.0, 

	0.0, 0.0, 1.0, 0.0, 
	0.0, 0.0, 1.0, 0.0, 
	0.0, 0.0, 1.0, 0.0, 
	0.0, 0.0, 1.0, 0.0, 
	0.0, 0.0, 1.0, 0.0, 
	0.0, 0.0, 1.0, 0.0, 
};
static const unsigned plane_count = 6;

const char* vert_filepath = "data/gl_shader.vert";
const char* frag_filepath = "data/gl_shader.frag";
const char* uniform_locations[] = {"os_to_ws", "ws_to_cs", "ws_to_ls", "projection", "directionalLight_ws"};
const unsigned num_of_uniforms = 5;
const char* attribute_locations[] = {"vertex", "uv", "normal", "tangent", "binormal"};
const unsigned num_of_attributes = 5;

bool AppRunning = true;

SDL_Surface* ScreenSurface = NULL;

glm::mat4 persp;
ShapeNode* shape = NULL;

void OnFrameDraw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 identity(1.0f);
	
	glm::vec3 eye(0.0f, 1.0f, -4.0f);
	glm::mat4 view = glm::lookAt(eye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2.0f, 2.0, 2.0));
	model = glm::rotate(model, sin(DeltaTime * glm::pi<float>() * 2.0f) * 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, DeltaTime * 360.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 light_dir(0.5f, -0.5f, 0.0f);
	light_dir = glm::normalize<float>(light_dir);
	
	glUniformMatrix4fv(Uniforms[0], 1, false, glm::value_ptr(model));
	glUniformMatrix4fv(Uniforms[1], 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(Uniforms[2], 1, false, glm::value_ptr(identity));
	glUniformMatrix4fv(Uniforms[3], 1, false, glm::value_ptr(persp));
	glUniform3fv(Uniforms[4], 1, glm::value_ptr(light_dir));
	shape->batch();

	SDL_GL_SwapBuffers();
}
void OnFrameUpdate()
{
	DeltaTime += 0.001f;
	if (DeltaTime > 1.0f) DeltaTime = 0.0f;
}
void OnFixedUpdate()
{
}

bool Reshape(unsigned width, unsigned height)
{
	ScreenSurface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_RESIZABLE);
	if (ScreenSurface == NULL) 
		return false;
	
	glViewport(0, 0, width, height);

	float aspect = float(width) / float(height);
	persp = glm::perspective(45.0f, aspect, 0.01f, 100.0f);

	return true;
}
bool Initialize(unsigned argc, char **argv)
{
	MALib::LOG_Initialize();
	MALib::RANDOM_Initialize();

	for (unsigned i = 0; i < argc; i++)
	{
		MALib::LOG_Message(argv[i]);
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		MALib::LOG_Message("Unable to initialize SDL.");
		MALib::LOG_Message(SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_WM_SetCaption("FractalDemo", "FractalDemo");

	Reshape(800, 600);
	
	GLenum glewStatus = glewInit();
	if (!GLEW_VERSION_3_0)
	{
		MALib::LOG_Message("Requires OpenGL 3.0 or later.");
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	
	MALib::LOG_Message("GLEW STATUS                ", (char*)glGetString(glewStatus));
	MALib::LOG_Message("GL VENDOR                  ", (char*)glGetString(GL_VENDOR));
	MALib::LOG_Message("GL RENDERER                ", (char*)glGetString(GL_RENDERER));
	MALib::LOG_Message("GL VERSION                 ", (char*)glGetString(GL_VERSION));
	MALib::LOG_Message("GL SHADING_LANGUAGE_VERSION", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	if (!BuildProgram(vert_filepath, frag_filepath))
	{
		MALib::LOG_Message("Could not build shaders.");
		return false;
	}
	if (!BindUniforms(uniform_locations, num_of_uniforms))
	{
		MALib::LOG_Message("Could not bind uniforms.");
		return false;
	}
	if (!BindAttributes(attribute_locations, num_of_attributes))
	{
		MALib::LOG_Message("Could not bind attributes.");
		return false;
	}

	MALib::LOG_Outiv("UNIFORMS", Uniforms.pointer(), Uniforms.length());
	MALib::LOG_Outiv("ATTRIBUTES", Attributes.pointer(), Attributes.length());

	MALib::OBJ_MESH* mesh = 0;
	MALib::ImportOBJFile("data/puzzle.obj", &mesh);
	float* buffer = 0;
	unsigned count = 0;
	MALib::BakeOBJ(mesh, &buffer, &count);

	shape = new ShapeNode();
	shape->initialize((void*)buffer, count);

	return true;
}
bool Unitialize()
{
	delete shape;

	SDL_Quit();
	MALib::LOG_Unitialize();
	return true;
}

HEX_END
#endif