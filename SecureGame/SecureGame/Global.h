#pragma once

#define ENABLE_CONSOLE false

#include <Windows.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Game.h"
#include "Shared.h"

namespace Global
{
    inline PVOID Enclave = nullptr;
    inline PENCLAVE_ROUTINE TickRoutine = nullptr;
}