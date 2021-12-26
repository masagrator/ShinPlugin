#include "main_patch.hpp"

void ReplaceSJIStoUTF8(std::vector<Text> Vector, const char* src, char* dst, int bufferSize, std::vector<Text>::iterator itr) {
	if (itr != Vector.end() && Vector[std::distance(Vector.begin(), itr)].ENG.size() <= (size_t)bufferSize) {
		memcpy(dst, Vector[std::distance(Vector.begin(), itr)].ENG.c_str(),
		       Vector[std::distance(Vector.begin(), itr)].ENG.size());
		return;
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

		return ReplaceSJIStoUTF8(Logic, src, dst, bufferSize,
					std::find_if(Logic.begin(), Logic.end(), find_JPN(compareJPN)));
	}
	else if (std::find(TreeOffsets.begin(), TreeOffsets.end(), offset) != TreeOffsets.end()) {
		auto offsetItr = std::distance(TreeOffsets.begin(),
					      std::find(TreeOffsets.begin(), TreeOffsets.end(), offset));

		char* checkJPN = (char*)calloc(1, bufferSize);
		SJIStoUTF8_original(src, bufferSize, checkJPN);
		std::string compareJPN = checkJPN;
		free(checkJPN);

		switch(offsetItr) {
			case 0:
			case 4:
				ReplaceSJIStoUTF8(Tree2C, src, dst, bufferSize, 
						 std::find_if(Tree2C.begin(), Tree2C.end(), find_JPN(compareJPN)));
				break;
			case 1:
				ReplaceSJIStoUTF8(Tree4C, src, dst, bufferSize,
						 std::find_if(Tree4C.begin(), Tree4C.end(), find_JPN(compareJPN)));
				break;
			case 2:
				ReplaceSJIStoUTF8(Tree8C, src, dst, bufferSize,
						 std::find_if(Tree8C.begin(), Tree8C.end(), find_JPN(compareJPN)));
				break;
			case 3:
				ReplaceSJIStoUTF8(TreeCC, src, dst, bufferSize,
						 std::find_if(TreeCC.begin(), TreeCC.end(), find_JPN(compareJPN)));
				break;
			default:
				SJIStoUTF8_original(src, bufferSize, dst);
				break;
		}
		return;

	}
	else return SJIStoUTF8_original(src, bufferSize, dst);
}

uint64_t Wins_YesNoWindow_Set_hook(int unk0, int unk1, int unk2, const char* string1, const char* string2) {
	if (strcmp(string1, "\x00") != 0) {
		std::string compare1 = string1;
		auto itr1 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(compare1));
		if (itr1 != YesNo.end()) string1 = YesNo[std::distance(YesNo.begin(), itr1)].ENG.c_str();
	}
	if (strcmp(string2, "\x00") != 0) {
		std::string compare2 = string2;
		auto itr2 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(compare2));
		if (itr2 != YesNo.end()) string2 = YesNo[std::distance(YesNo.begin(), itr2)].ENG.c_str();
	}
	return Wins_YesNoWindow_Set_original(unk0, unk1, unk2, string1, string2);
}

Result LoadModule_hook(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) {
	Result ret = LoadModule_original(pOutModule, pImage, buffer, bufferSize, 1);
	if (strcmp(pOutModule->pathToNro, "nro/Tfoaf1.nro") == 0) {
		uintptr_t pointer = 0;
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13UTF8toSJIS_NXPKciPc");
		memcpy((void**)&UTF8toSJIS_NX, &pointer, 8);
	
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13SJIStoUTF8_NXPKciPc");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(SJIStoUTF8_hook),
			(void**)&SJIStoUTF8_original);
		
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_ZN12clsNameInput16SetLastSelectStrEv");
		NRO_Tfoaf1_start = pointer - 0x7000;

		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z20Wins_YesNoWindow_SetiiiPKcS0_");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(Wins_YesNoWindow_Set_hook),
			(void**)&Wins_YesNoWindow_Set_original);
	}
	return ret;
}

void tfoaf_main()
{
	A64HookFunction((void**)&nn::ro::LoadModule,
			reinterpret_cast<void*>(LoadModule_hook),
			(void**)&LoadModule_original);
}
