#pragma once

#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"
#include "skyline/inlinehook/memcpy_controlled.hpp"
#include "nn/ro.h"
#include "Tree.hpp"
#include "Logic.hpp"
#include "YesNo.hpp"
#include "TextView_Render.hpp"
#define LINKABLE __attribute__ ((weak))

extern "C" {
	void _ZN4Nmpl9Framework7GraUtil13CMojiFontDrawC1ERNS1_9CMojiFontE(void* unk0, void* unk1, void* unk2) LINKABLE;
}

struct CMojiFont {
	char reserved[38];
	bool varWidth;
};

struct find_JPN {
	const char* JPN;
	find_JPN(const char* JPN) : JPN(JPN) {}
	bool operator () ( const Text& m ) const
	{
		return !strncmp(m.JPN, JPN, strlen(m.JPN));
	}
};

uintptr_t NRO_Tfoaf_start = 0;
bool ShinHaya1_set = false;

Result nn::ro::LoadModule(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) LINKABLE;
Result nn::ro::LookupModuleSymbol(uintptr_t* pOutAddress, const Module* pModule, const char* name) LINKABLE;

void (*SJIStoUTF8_original)(char const* src, int bufferSize, char* dst);
Result (*LoadModule_original)(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag);
void (*CMojiFontDraw_original)(CMojiFont* unk0, void* unk1, void* unk2);
uint32_t (*GetLastX_original)(void);