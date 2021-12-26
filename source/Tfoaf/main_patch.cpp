#include "main_patch.hpp"

void ReplaceSJIStoUTF8(std::vector<Text> Vector, const char* src, char* dst, int bufferSize, std::vector<Text>::iterator itr) {
	if (itr != Vector.end()) {
		if (Vector[std::distance(Vector.begin(), itr)].ENG.size() <= (size_t)bufferSize) {
			memcpy(dst, Vector[std::distance(Vector.begin(), itr)].ENG.c_str(), Vector[std::distance(Vector.begin(), itr)].ENG.size());
			return;
		}
	}
	return SJIStoUTF8_original(src, bufferSize, dst);
}

void SJIStoUTF8_hook(char const* src, int bufferSize, char* dst) {
	uintptr_t LR = (uintptr_t)__builtin_return_address(0);

	ptrdiff_t offset = LR - NRO_Tfoaf1_start;

	if (offset == LogicOffset) {
		char* checkJPN = (char*)calloc(1, bufferSize);
		SJIStoUTF8_original(src, bufferSize, checkJPN);

		std::string compareJPN = checkJPN;
		free(checkJPN);

		auto itrLogic = std::find_if(Logic.begin(), Logic.end(), find_JPN(compareJPN));

		return ReplaceSJIStoUTF8(Logic, src, dst, bufferSize, itrLogic);
	}
	else if (std::find(TreeOffsets.begin(), TreeOffsets.end(), offset) != TreeOffsets.end()) {
		auto itr = std::find(TreeOffsets.begin(), TreeOffsets.end(), offset);
		auto offsetItr = std::distance(TreeOffsets.begin(), itr);

		char* checkJPN = (char*)calloc(1, bufferSize);
		SJIStoUTF8_original(src, bufferSize, checkJPN);
		std::string compareJPN = checkJPN;
		free(checkJPN);

		std::vector<Text>::iterator itrTree;
		switch(offsetItr) {
			case 0:
			case 4:
				itrTree = std::find_if(Tree2C.begin(), Tree2C.end(), find_JPN(compareJPN));
				ReplaceSJIStoUTF8(Tree2C, src, dst, bufferSize, itrTree);
				break;
			case 1:
				itrTree = std::find_if(Tree4C.begin(), Tree4C.end(), find_JPN(compareJPN));
				ReplaceSJIStoUTF8(Tree4C, src, dst, bufferSize, itrTree);
				break;
			case 2:
				itrTree = std::find_if(Tree8C.begin(), Tree8C.end(), find_JPN(compareJPN));
				ReplaceSJIStoUTF8(Tree8C, src, dst, bufferSize, itrTree);
				break;
			case 3:
				itrTree = std::find_if(TreeCC.begin(), TreeCC.end(), find_JPN(compareJPN));
				ReplaceSJIStoUTF8(TreeCC, src, dst, bufferSize, itrTree);
				break;
			default:
				SJIStoUTF8_original(src, bufferSize, dst);
				break;
		}
		return;

	}
	else return SJIStoUTF8_original(src, bufferSize, dst);
}

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
