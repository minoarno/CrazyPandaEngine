#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#include <stdexcept>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push)
#pragma warning(disable : 4189)
#pragma warning(disable : 4201)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)
#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "HelperStructs.h"
#include "HelperFunctions.h"
#pragma warning (pop)