#ifndef EMULATOR_FILESYSTEM_EMSCRIPTEN_H
#define EMULATOR_FILESYSTEM_EMSCRIPTEN_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"

#if defined(_WIN32) || defined(_WIN64)
extern void Emulator_OpenReadWIN(long hash, void* buff, int size);
extern void Emulator_OpenReadFPWIN(const char* filePath, void* buff, int size);
extern void Emulator_GetFileSizeWIN(const char* filePath, int* outSize);
extern void Emulator_ReadFileWIN(const char* filePath, void* buff, int size);
#endif

#endif