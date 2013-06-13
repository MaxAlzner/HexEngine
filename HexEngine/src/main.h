#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <math.h>
#include <time.h>
#include <vector>

#include <Windows.h>

#include <GL\glew.h>
#include <SDL.h>

void OnFrame();
void OnTick();
void OnKey(char code);

bool BuildShader(GLuint* program, const char* vert_loc, const char* frag_loc, const char** outError = NULL);
bool BindUniforms(GLuint program, const char** uniform_locations, unsigned int size);
bool BindAttributes(GLuint program, const char** attributes, unsigned int size);

bool Reshape(int width, int height);
bool Listen(SDL_Event &event);
bool Init();
bool Uninit();