#pragma once

#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include "nn/ro.h"
#include "Tree.hpp"
#include "Logic.hpp"
#define LINKABLE __attribute__ ((weak))

struct find_JPN {
	std::string JPN;
	find_JPN(std::string JPN) : JPN(JPN) {}
	bool operator () ( const Text& m ) const
	{
		return m.JPN == JPN;
	}
};

uintptr_t NRO_Tfoaf1_start = 0;
Result nn::ro::LoadModule(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) LINKABLE;
Result nn::ro::LookupModuleSymbol(uintptr_t* pOutAddress, const Module* pModule, const char* name) LINKABLE;


void (*UTF8toSJIS_NX)(char const* src, int bufferSize, char* dst);

void (*SJIStoUTF8_original)(char const* src, int bufferSize, char* dst);

Result (*LoadModule_original)(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag);