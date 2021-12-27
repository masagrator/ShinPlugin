#pragma once

#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"
#include "skyline/inlinehook/memcpy_controlled.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include "nn/ro.h"
#include "Tree.hpp"
#include "Logic.hpp"
#include "YesNo.hpp"
#include "TextView_Render.hpp"
#define LINKABLE __attribute__ ((weak))

extern "C" {
	void _ZN4Nmpl9Framework7GraUtil13CMojiFontDrawC1ERNS1_9CMojiFontE(void* unk0, void* unk1, void* unk2) LINKABLE;
}

struct find_JPN {
	std::string JPN;
	find_JPN(std::string JPN) : JPN(JPN) {}
	bool operator () ( const Text& m ) const
	{
		return m.JPN == JPN;
	}
};



uintptr_t NRO_Tfoaf1_start = 0;
uintptr_t notDuospaced = false;

Result nn::ro::LoadModule(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) LINKABLE;
Result nn::ro::LookupModuleSymbol(uintptr_t* pOutAddress, const Module* pModule, const char* name) LINKABLE;

void (*UTF8toSJIS_NX)(char const* src, int bufferSize, char* dst);
void (*SJIStoUTF8_original)(char const* src, int bufferSize, char* dst);
Result (*LoadModule_original)(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag);
void (*CMojiFontDraw_original)(void* unk0, void* unk1, void* unk2);