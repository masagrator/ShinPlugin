#include "main_patch.hpp"
#include <span>

ptrdiff_t returnInstructionOffset(uintptr_t LR) {
	return LR - NRO_Tfoaf1_start;
}

void ReplaceSJIStoUTF8(std::span<Text> Vector, const char* src, char* dst, int bufferSize, std::span<Text>::iterator itr) {
	if (itr != Vector.end() && strlen(itr->ENG) <= (size_t)bufferSize) {
		memcpy(dst, itr->ENG, strlen(itr->ENG));
		return;
	}
	return SJIStoUTF8_original(src, bufferSize, dst);
}

void SJIStoUTF8_hook(char const* src, int bufferSize, char* dst) {
	ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));

	if (ShinHaya1_set) {
		if (offset == SH1::LogicOffset) {
			char* checkJPN = (char*)calloc(1, bufferSize);
			SJIStoUTF8_original(src, bufferSize, checkJPN);

			ReplaceSJIStoUTF8(SH1::Logic, src, dst, bufferSize,
						std::find_if(SH1::Logic.begin(), SH1::Logic.end(), find_JPN(checkJPN)));
			free(checkJPN);
			return;
		}
		else if (std::find(SH1::TreeOffsets.begin(), SH1::TreeOffsets.end(), offset) != SH1::TreeOffsets.end()) {
			auto offsetItr = std::distance(SH1::TreeOffsets.begin(),
							std::find(SH1::TreeOffsets.begin(), SH1::TreeOffsets.end(), offset));

			char* checkJPN = (char*)calloc(1, bufferSize);
			SJIStoUTF8_original(src, bufferSize, checkJPN);

			switch(offsetItr) {
				case 0:
				case 4:
					ReplaceSJIStoUTF8(SH1::Tree2C, src, dst, bufferSize, 
							std::find_if(SH1::Tree2C.begin(), SH1::Tree2C.end(), find_JPN(checkJPN)));
					break;
				case 1:
					ReplaceSJIStoUTF8(SH1::Tree4C, src, dst, bufferSize,
							std::find_if(SH1::Tree4C.begin(), SH1::Tree4C.end(), find_JPN(checkJPN)));
					break;
				case 2:
					ReplaceSJIStoUTF8(SH1::Tree8C, src, dst, bufferSize,
							std::find_if(SH1::Tree8C.begin(), SH1::Tree8C.end(), find_JPN(checkJPN)));
					break;
				case 3:
					ReplaceSJIStoUTF8(SH1::TreeCC, src, dst, bufferSize,
							std::find_if(SH1::TreeCC.begin(), SH1::TreeCC.end(), find_JPN(checkJPN)));
					break;
				default:
					SJIStoUTF8_original(src, bufferSize, dst);
					break;
			}
			free(checkJPN);
			return;

		}
	}
	else {

	}
	return SJIStoUTF8_original(src, bufferSize, dst);
}

uint64_t Wins_YesNoWindow_Set_hook(int unk0, int unk1, int unk2, const char* string1, const char* string2) {
	if (strncmp(string1, "\x00", 1) != 0) {
		auto itr1 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(string1));
		if (itr1 != YesNo.end()) string1 = itr1->ENG;
	}
	if (strncmp(string2, "\x00", 1) != 0) {
		auto itr2 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(string2));
		if (itr2 != YesNo.end()) string2 = itr2->ENG;
	}
	return Wins_YesNoWindow_Set_original(unk0, unk1, unk2, string1, string2);
}

int store_X1 = 0;
int store_X2 = 0;
int store_Y1 = 0;

uint64_t DrawText_hook(int Pos_X, int Pos_Y, int Pos_Z, unsigned int w3, float ScaleX, float ScaleY, char const* Text, int w4) {
	ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));

	if (ShinHaya1_set) {
		if (std::find(SH1::NMSTextOffsets.begin(), SH1::NMSTextOffsets.end(), offset) != SH1::NMSTextOffsets.end()) {
			static int Old_X = 0;
			static int Old_Y = 0;
			static int64_t OldText_width = 0;

			if ((Pos_X > Old_X) && (Old_Y == Pos_Y)) {
				Pos_X = Old_X + OldText_width;
			}

			OldText_width = getDrawTextWidth(Text, ScaleX);
			store_X1 = Pos_X + OldText_width;
			Old_X = Pos_X;

			if (offset == SH1::NMSTextOffsets[2]) {	//Write manually offset for CompletionMark if Select offset is detected

				/*Completion mark has hardcoded entry for each select in NRO.
				Each entry takes size of 0x5C.
				We need to take this to account to not overwrite previous rows.*/

				static int Select_row_line = 0;
				if (Old_Y < Pos_Y) Select_row_line += 1;
				else if (Old_Y > Pos_Y) Select_row_line = 0;
				ptrdiff_t RowEntry = 0x5C * Select_row_line;

				uint32_t* CompletionMarkOffset = (uint32_t*)(NRO_Tfoaf1_start + 0x11CAB08 + RowEntry);
				*CompletionMarkOffset = store_X1;
			}
			
			Old_Y = store_Y1 = Pos_Y;
		}
	}
	else {

	}
	return DrawText_original(Pos_X, Pos_Y, Pos_Z, w3, ScaleX, ScaleY, Text, w4);
}

int32_t GetLastX_hook(void) {
	ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));
	if (ShinHaya1_set) {
		if (std::find(SH1::GetLastXOffsets.begin(), SH1::GetLastXOffsets.end(), offset) != SH1::GetLastXOffsets.end()) {
			auto offsetItr = std::distance(SH1::GetLastXOffsets.begin(), std::find(SH1::GetLastXOffsets.begin(), SH1::GetLastXOffsets.end(), offset));
			switch (offsetItr) {
				case 0:
					if (NmsTextView_GetLastY() != store_Y1)
						store_X1 = GetLastX_original();
					return store_X1;
				case 1:
					int value = store_X1 + store_X2;
					store_X2 = 0;
					return value;
			}
		}
	}
	else {

	}
	return GetLastX_original();
}

char* PutCodeTo_hook(void* _NMS_CTL_PARAM, unsigned char byte1, unsigned char byte2) {
	static bool Keyword = false;
	static char* textBufferSJIS = 0;
	static char* textBufferUTF8 = 0;
	static uint8_t offset = 0;
	if ((byte1 == 0x81) && (byte2 == 0x6b)) {
		offset = 0;
		byte1 = 0x5B;
		byte2 = 0;
		textBufferSJIS = (char*)calloc(1, 0x40);
		textBufferUTF8 = (char*)calloc(1, 0x40);
		Keyword = true;
		memcpy(textBufferSJIS, &byte1, 1);
		//memcpy(textBufferSJIS+1, &byte2, 1);
		offset = 1;
	}
	else if ((byte1 == 0x81) && (byte2 == 0x6c)) {
		Keyword = false;
		byte1 = 0x5D;
		byte2 = 0;
		memcpy(textBufferSJIS+offset, &byte1, 1);
		//memcpy(textBufferSJIS+offset+1, &byte2, 1);
		SJIStoUTF8_original(textBufferSJIS, 0x40, textBufferUTF8);
		store_X2 = getDrawTextWidth(textBufferUTF8, 1.0);
		free(textBufferSJIS);
		free(textBufferUTF8);
	}
	else if (Keyword == true) {
		if (byte1 != 0) {
			memcpy(textBufferSJIS+offset, &byte1, 1);
			offset += 1;
		}
		if (byte2 != 0) {
			memcpy(textBufferSJIS+offset, &byte2, 1);
			offset += 1;
		}
	}
	return PutCodeTo_original(_NMS_CTL_PARAM, byte1, byte2);
}

void patchTfoaf1Code() {
	uint8_t NOP_code[4] = {0x1F, 0x20, 0x03, 0xD5};

	// Offsets that NOPped are forcing game to use for MC name string from gamestrings instead of user name
	ptrdiff_t nopUserNameMainWindow_offset = 0x536E0;
	ptrdiff_t nopUserNameBacklog_offset = 0x53CBC;

	/*Offset that NOPped is blocking writing CompletionMark X offset by game.
	Check DrawText hook that is taking job of writing X offset.*/
	ptrdiff_t nopCompletionMarkPosX_offset = 0x37CAC;

	sky_memcpy((void*)(NRO_Tfoaf1_start + nopUserNameMainWindow_offset), 
					&NOP_code, 4);
	sky_memcpy((void*)(NRO_Tfoaf1_start + nopUserNameBacklog_offset), 
					&NOP_code, 4);
	
	sky_memcpy((void*)(NRO_Tfoaf1_start + nopCompletionMarkPosX_offset), 
					&NOP_code, 4);

	return;
}

Result LoadModule_hook(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) {
	Result ret = LoadModule_original(pOutModule, pImage, buffer, bufferSize, 1);
	if (strcmp(pOutModule->pathToNro, "nro/Tfoaf1.nro") == 0) {
		ShinHaya1_set = true;

		/* Hook function responsible for converting text between encodings
		to replace text in certain parts of game on the fly.*/
		uintptr_t pointer = 0;
	
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13SJIStoUTF8_NXPKciPc");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(SJIStoUTF8_hook),
			(void**)&SJIStoUTF8_original);

		// Hook Yes/No Window to replace hardcoded text
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z20Wins_YesNoWindow_SetiiiPKcS0_");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(Wins_YesNoWindow_Set_hook),
			(void**)&Wins_YesNoWindow_Set_original);
		
		// Hook DrawText to repair issue with rendering separated parts of text in one line
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z8DrawTextiiijPKcffi");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(DrawText_hook),
			(void**)&DrawText_original);
		
		// Hook GetLastX and PutCode to repair Ruby effect
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z20NmsTextView_GetLastXv");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(GetLastX_hook),
			(void**)&GetLastX_original);

		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z16NmsCtl_PutCodeToP14_NMS_CTL_PARAMhh");
		A64HookFunction((void*)pointer,
			reinterpret_cast<void*>(PutCodeTo_hook),
			(void**)&PutCodeTo_original);

		// Find symbol to determine NRO start pointer
		nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_ZN12clsNameInput16SetLastSelectStrEv");
		NRO_Tfoaf1_start = pointer - 0x7000;
		patchTfoaf1Code();
		
	}
	return ret;
}


void CMojiFontDraw_hook(void* fontPtr, void* unk1, void* unk2) {

	CMojiFontDraw_original(fontPtr, unk1, unk2);

	bool notDuospaced = true;
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
