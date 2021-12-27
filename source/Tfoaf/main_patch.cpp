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
	if (strncmp(string1, "\x00", 1) != 0) {
		std::string compare1 = string1;
		auto itr1 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(compare1));
		if (itr1 != YesNo.end()) string1 = YesNo[std::distance(YesNo.begin(), itr1)].ENG.c_str();
	}
	if (strncmp(string2, "\x00", 1) != 0) {
		std::string compare2 = string2;
		auto itr2 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(compare2));
		if (itr2 != YesNo.end()) string2 = YesNo[std::distance(YesNo.begin(), itr2)].ENG.c_str();
	}
	return Wins_YesNoWindow_Set_original(unk0, unk1, unk2, string1, string2);
}

void patchTfoaf1Code() {
	// Patches for reversing YES NO
	uint8_t reverseYesNoResult_code[4] = {0x1F, 0x01, 0x00, 0x71};
	uint8_t reverseCancelOK_YesNoSounds_code[4] = {0x15, 0x09, 0x00, 0x35};
	uint8_t notInterpretBackAsYes_code[4] = {0xE0, 0x2E, 0x00, 0x79};
	// Patch that removes option to write user name instead of true MC name
	uint8_t nopUserName_code[4] = {0x1F, 0x20, 0x03, 0xD5};

	ptrdiff_t reverseYesNoResult_ptr = 0x559E0;
	ptrdiff_t reverseCancelOK_YesNoSounds_ptr = 0x54608;
	ptrdiff_t notInterpretBackAsYes_ptr = 0x54720;
	ptrdiff_t nopUserNameMainWindow_ptr = 0x536E0;
	ptrdiff_t nopUserNameBacklog_ptr = 0x53CBC;

	sky_memcpy((void*)(NRO_Tfoaf1_start + reverseYesNoResult_ptr), 
					&reverseYesNoResult_code, 4);
	sky_memcpy((void*)(NRO_Tfoaf1_start + reverseCancelOK_YesNoSounds_ptr), 
					&reverseCancelOK_YesNoSounds_code, 4);
	sky_memcpy((void*)(NRO_Tfoaf1_start + notInterpretBackAsYes_ptr), 
					&notInterpretBackAsYes_code, 4);
	sky_memcpy((void*)(NRO_Tfoaf1_start + nopUserNameMainWindow_ptr), 
					&nopUserName_code, 4);
	sky_memcpy((void*)(NRO_Tfoaf1_start + nopUserNameBacklog_ptr), 
					&nopUserName_code, 4);

	return;
}

Result LoadModule_hook(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) {
	Result ret = LoadModule_original(pOutModule, pImage, buffer, bufferSize, 1);
	if (strcmp(pOutModule->pathToNro, "nro/Tfoaf1.nro") == 0) {

		/* Hook two functions responsible for converting text between encodings
		to replace text in certain parts of games on the fly.*/
		uintptr_t pointer = 0;
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13UTF8toSJIS_NXPKciPc");
		memcpy((void**)&UTF8toSJIS_NX, &pointer, 8);
	
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13SJIStoUTF8_NXPKciPc");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(SJIStoUTF8_hook),
			(void**)&SJIStoUTF8_original);

		// Hook Yes/No Window to replace hardcoded text
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z20Wins_YesNoWindow_SetiiiPKcS0_");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(Wins_YesNoWindow_Set_hook),
			(void**)&Wins_YesNoWindow_Set_original);
		
		// Find symbol to determine NRO start pointer
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_ZN12clsNameInput16SetLastSelectStrEv");
		NRO_Tfoaf1_start = pointer - 0x7000;
		patchTfoaf1Code();
		
	}
	return ret;
}


void CMojiFontDraw_hook(void* fontPtr, void* unk1, void* unk2) {

	CMojiFontDraw_original(fontPtr, unk1, unk2);

	notDuospaced = true;
	memcpy((void*)((uintptr_t)fontPtr+38), &notDuospaced, 1);
	return;
}

void tfoaf_main()
{
	//Hook NRO loading
	A64HookFunction((void**)&nn::ro::LoadModule,
			reinterpret_cast<void*>(LoadModule_hook),
			(void**)&LoadModule_original);

	//Hook Font Generation
	A64HookFunction((void**)&_ZN4Nmpl9Framework7GraUtil13CMojiFontDrawC1ERNS1_9CMojiFontE,
			reinterpret_cast<void*>(CMojiFontDraw_hook),
			(void**)&CMojiFontDraw_original);
}
