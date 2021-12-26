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
void SJIStoUTF8_hook(char const* src, int bufferSize, char* dst) {
	uintptr_t LR = (uintptr_t)__builtin_return_address(0);

	uintptr_t offset = LR - NRO_Tfoaf1_start;

	if (offset == LogicOffset) {
		char* checkJPN = (char*)calloc(1, bufferSize);
		SJIStoUTF8_original(src, bufferSize, checkJPN);

		std::string compareJPN = checkJPN;
		free(checkJPN);

		auto itrLogic = std::find_if(Logic.begin(), Logic.end(), find_JPN(compareJPN));

		if (itrLogic != Logic.end()) {
			char* newText = (char*)calloc(1, bufferSize);
			UTF8toSJIS_NX(Logic[std::distance(Logic.begin(), itrLogic)].ENG.c_str(), bufferSize, newText);
			SJIStoUTF8_original(newText, bufferSize, dst);
			free(newText);
			return;
		}
		else return SJIStoUTF8_original(src, bufferSize, dst);
	}
	else if (std::find(TreeOffsets.begin(), TreeOffsets.end(), offset) != TreeOffsets.end()) {
		auto itr = std::find(TreeOffsets.begin(), TreeOffsets.end(), offset);
		auto offsetItr = std::distance(TreeOffsets.begin(), itr);

		char* checkJPN = (char*)calloc(1, bufferSize);
		SJIStoUTF8_original(src, bufferSize, checkJPN);
		std::string compareJPN = checkJPN;
		free(checkJPN);

		char* newText = (char*)calloc(1, bufferSize);
		std::vector<Text>::iterator itrText;
		switch(offsetItr) {
			case 0:
			case 4:
				itrText = std::find_if(Tree2C.begin(), Tree2C.end(), find_JPN(compareJPN));
				if (itrText != Tree2C.end()) {
					UTF8toSJIS_NX(Tree2C[std::distance(Tree2C.begin(), itrText)].ENG.c_str(), bufferSize, newText);
					SJIStoUTF8_original(newText, bufferSize, dst);
					return;
				}
				else SJIStoUTF8_original(src, bufferSize, dst);
				break;
			case 1:
				itrText = std::find_if(Tree4C.begin(), Tree4C.end(), find_JPN(compareJPN));
				if (itrText != Tree4C.end()) {
					UTF8toSJIS_NX(Tree4C[std::distance(Tree4C.begin(), itrText)].ENG.c_str(), bufferSize, newText);
					SJIStoUTF8_original(newText, bufferSize, dst);
					return;
				}
				else SJIStoUTF8_original(src, bufferSize, dst);
				break;
			case 2:
				itrText = std::find_if(Tree8C.begin(), Tree8C.end(), find_JPN(compareJPN));
				if (itrText != Tree8C.end()) {
					UTF8toSJIS_NX(Tree8C[std::distance(Tree8C.begin(), itrText)].ENG.c_str(), bufferSize, newText);
					SJIStoUTF8_original(newText, bufferSize, dst);
					return;
				}
				else SJIStoUTF8_original(src, bufferSize, dst);
				break;
			case 3:
				itrText = std::find_if(TreeCC.begin(), TreeCC.end(), find_JPN(compareJPN));
				if (itrText != TreeCC.end()) {
					UTF8toSJIS_NX(TreeCC[std::distance(TreeCC.begin(), itrText)].ENG.c_str(), bufferSize, newText);
					SJIStoUTF8_original(newText, bufferSize, dst);
					return;
				}
				else SJIStoUTF8_original(src, bufferSize, dst);
				break;
			default:
				SJIStoUTF8_original(src, bufferSize, dst);
				break;
		}
		free(newText);
		return;

	}
	else return SJIStoUTF8_original(src, bufferSize, dst);
}

Result (*LoadModule_original)(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag);
Result LoadModule_hook(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) {
	Result ret = LoadModule_original(pOutModule, pImage, buffer, bufferSize, 1);
	if (strcmp(pOutModule->pathToNro, "nro/Tfoaf1.nro") == 0) {
		uintptr_t UTF8toSJIS_PTR = 0;
		nn::ro::LookupModuleSymbol(&UTF8toSJIS_PTR, pOutModule, "_Z13UTF8toSJIS_NXPKciPc");
		memcpy((void**)&UTF8toSJIS_NX, &UTF8toSJIS_PTR, 8);
	
		uintptr_t pointer = 0;
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13SJIStoUTF8_NXPKciPc");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(SJIStoUTF8_hook),
			(void**)&SJIStoUTF8_original);
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_ZN12clsNameInput16SetLastSelectStrEv");
		NRO_Tfoaf1_start = pointer - 0x7000;
	}
	return ret;
}

void tfoaf_main()
{
	A64HookFunction((void**)&nn::ro::LoadModule,
			reinterpret_cast<void*>(LoadModule_hook),
			(void**)&LoadModule_original);
}
