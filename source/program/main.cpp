#include "lib.hpp"
#include "nn/ro.h"
#include <span>
#include <algorithm>
#include "Tree.hpp"
#include "Logic.hpp"
#include "YesNo.hpp"
#include "TextView_Render.hpp"

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
uintptr_t SJIStoUTF8_origin = 0;

extern "C" {
	// This function has only one argument, but two more are used to fix issue with segfault
	void _ZN4Nmpl9Framework7GraUtil13CMojiFontDrawC1ERNS1_9CMojiFontE(CMojiFont* fontPtr, void* unk1, void* unk2);
    typedef void (*SjisToUtf8)(char const* src, int bufferSize, char* dst);
}

ptrdiff_t returnInstructionOffset(uintptr_t LR) {
	return LR - NRO_Tfoaf_start;
}

/* Define hook StubCopyright. Trampoline indicates the original function should be kept. */
/* HOOK_DEFINE_REPLACE can be used if the original function does not need to be kept. */
HOOK_DEFINE_TRAMPOLINE(CMojiFontDraw) {

    /* Define the callback for when the function is called. Don't forget to make it static and name it Callback. */
    static void Callback(CMojiFont* fontPtr, void* unk1, void* unk2) {

        /* Call the original function, with the argument always being false. */
        Orig(fontPtr, unk1, unk2);
        fontPtr -> varWidth = true;
    }

};

bool ReplaceSJIStoUTF8(std::span<Text> Vector, const char* src, char* dst, int bufferSize, std::span<Text>::iterator itr) {
	if (itr != Vector.end() && strlen(itr->ENG) <= (size_t)bufferSize) {
		memcpy(dst, itr->ENG, strlen(itr->ENG));
		return true;
	}
    return false;
}

HOOK_DEFINE_TRAMPOLINE(SJIStoUTF8) {

    static void Callback(char const* src, int bufferSize, char* dst) {
        ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));

        if (ShinHaya1_set) {
            if (offset == SH1::LogicOffset) {
                char* checkJPN = (char*)calloc(1, bufferSize);
                Orig(src, bufferSize, checkJPN);

                if (!ReplaceSJIStoUTF8(SH1::Logic, src, dst, bufferSize,
                    std::find_if(SH1::Logic.begin(), SH1::Logic.end(), find_JPN(checkJPN))))
                    Orig(src, bufferSize, dst);
                
                free(checkJPN);
                return;
            }
            else if (std::find(SH1::TreeOffsets.begin(), SH1::TreeOffsets.end(), offset) != SH1::TreeOffsets.end()) {
                auto offsetItr = std::distance(SH1::TreeOffsets.begin(),
                                std::find(SH1::TreeOffsets.begin(), SH1::TreeOffsets.end(), offset));

                char* checkJPN = (char*)calloc(1, bufferSize);
                Orig(src, bufferSize, checkJPN);

                switch(offsetItr) {
                    case 0:
                    case 4:
                        if (!ReplaceSJIStoUTF8(SH1::Tree2C, src, dst, bufferSize, 
                            std::find_if(SH1::Tree2C.begin(), SH1::Tree2C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 1:
                        if (!ReplaceSJIStoUTF8(SH1::Tree4C, src, dst, bufferSize, 
                            std::find_if(SH1::Tree2C.begin(), SH1::Tree4C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 2:
                        if (!ReplaceSJIStoUTF8(SH1::Tree8C, src, dst, bufferSize, 
                            std::find_if(SH1::Tree2C.begin(), SH1::Tree8C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 3:
                        if (!ReplaceSJIStoUTF8(SH1::TreeCC, src, dst, bufferSize, 
                            std::find_if(SH1::Tree2C.begin(), SH1::TreeCC.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                }
                free(checkJPN);
                return;

            }
        }
        else {
            if (offset == SH2::LogicOffset) {
                char* checkJPN = (char*)calloc(1, bufferSize);
                Orig(src, bufferSize, checkJPN);

                if (!ReplaceSJIStoUTF8(SH2::Logic, src, dst, bufferSize,
                    std::find_if(SH2::Logic.begin(), SH2::Logic.end(), find_JPN(checkJPN))))
                    Orig(src, bufferSize, dst);
                free(checkJPN);
                return;
            }
            else if (std::find(SH2::TreeOffsets.begin(), SH2::TreeOffsets.end(), offset) != SH2::TreeOffsets.end()) {
                auto offsetItr = std::distance(SH2::TreeOffsets.begin(),
                                std::find(SH2::TreeOffsets.begin(), SH2::TreeOffsets.end(), offset));

                char* checkJPN = (char*)calloc(1, bufferSize);
                Orig(src, bufferSize, checkJPN);

                switch(offsetItr) {
                    case 0:
                    case 4:
                        if (!ReplaceSJIStoUTF8(SH2::Tree2C, src, dst, bufferSize, 
                            std::find_if(SH2::Tree2C.begin(), SH2::Tree2C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 1:
                        if (!ReplaceSJIStoUTF8(SH2::Tree6C, src, dst, bufferSize, 
                            std::find_if(SH2::Tree6C.begin(), SH2::Tree6C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 2:
                        if (!ReplaceSJIStoUTF8(SH2::TreeAC, src, dst, bufferSize, 
                            std::find_if(SH2::TreeAC.begin(), SH2::TreeAC.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 3:
                        if (!ReplaceSJIStoUTF8(SH2::TreeEC, src, dst, bufferSize, 
                            std::find_if(SH2::TreeEC.begin(), SH2::TreeEC.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                }
                free(checkJPN);
                return;

            }
        }
        return Orig(src, bufferSize, dst);
    }

};

HOOK_DEFINE_TRAMPOLINE(Wins_YesNoWindow) {

    static uint64_t Callback(int unk0, int unk1, int unk2, const char* string1, const char* string2) {
        if (string1[0]) {
            auto itr1 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(string1));
            if (itr1 != YesNo.end()) string1 = itr1->ENG;
        }
        if (string2[0]) {
            auto itr2 = std::find_if(YesNo.begin(), YesNo.end(), find_JPN(string2));
            if (itr2 != YesNo.end()) string2 = itr2->ENG;
        }
        return Orig(unk0, unk1, unk2, string1, string2);
    }

};

int store_X1 = 0;
int store_X2 = 0;
int store_Y1 = 0;

HOOK_DEFINE_TRAMPOLINE(DrawText) {

    static uint64_t Callback(int Pos_X, int Pos_Y, int Pos_Z, unsigned int w3, float ScaleX, float ScaleY, char const* Text, int w4) {
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

                if (offset == SH1::NMSTextOffsets[0]) {	//Write manually offset for CompletionMark if Select offset is detected

                    /*Completion mark has hardcoded entry for each select in NRO.
                    Each entry takes size of 0x5C.
                    We need to take this to account to not overwrite previous rows.*/

                    static int Select_row_line = 0;
                    if (Old_Y < Pos_Y) Select_row_line += 1;
                    else if (Old_Y > Pos_Y) Select_row_line = 0;
                    ptrdiff_t RowEntry = 0x5C * Select_row_line;

                    uint32_t* CompletionMarkOffset = (uint32_t*)(NRO_Tfoaf_start + 0x11CAB08 + RowEntry);
                    *CompletionMarkOffset = store_X1;
                }
                
                Old_Y = store_Y1 = Pos_Y;
            }
        }
        else if (std::find(SH2::NMSTextOffsets.begin(), SH2::NMSTextOffsets.end(), offset) != SH2::NMSTextOffsets.end()) {
            static int Old_X = 0;
            static int Old_Y = 0;
            static int64_t OldText_width = 0;

            if ((Pos_X > Old_X) && (Old_Y == Pos_Y)) {
                Pos_X = Old_X + OldText_width;
            }

            OldText_width = getDrawTextWidth(Text, ScaleX);
            store_X1 = Pos_X + OldText_width;
            Old_X = Pos_X;

            if (offset == SH2::NMSTextOffsets[0]) {	//Write manually offset for CompletionMark if Select offset is detected

                /*Completion mark has hardcoded entry for each select in NRO.
                Each entry takes size of 0x5C.
                We need to take this to account to not overwrite previous rows.*/

                static int Select_row_line = 0;
                if (Old_Y < Pos_Y) Select_row_line += 1;
                else if (Old_Y > Pos_Y) Select_row_line = 0;
                ptrdiff_t RowEntry = 0x5C * Select_row_line;

                uint32_t* CompletionMarkOffset = (uint32_t*)(NRO_Tfoaf_start + 0x11DB0D0 + RowEntry);
                *CompletionMarkOffset = store_X1;
            }
            
            Old_Y = store_Y1 = Pos_Y;
        }
        return Orig(Pos_X, Pos_Y, Pos_Z, w3, ScaleX, ScaleY, Text, w4);
    }

};

HOOK_DEFINE_TRAMPOLINE(GetLastX) {

    static int32_t Callback(void) {
        ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));
        auto offsetItr = -1;

        if (ShinHaya1_set) {
            if (std::find(SH1::GetLastXOffsets.begin(), SH1::GetLastXOffsets.end(), offset) != SH1::GetLastXOffsets.end())
                offsetItr = std::distance(SH1::GetLastXOffsets.begin(), std::find(SH1::GetLastXOffsets.begin(), SH1::GetLastXOffsets.end(), offset));
        }
        else if (std::find(SH2::GetLastXOffsets.begin(), SH2::GetLastXOffsets.end(), offset) != SH2::GetLastXOffsets.end())
            offsetItr = std::distance(SH2::GetLastXOffsets.begin(), std::find(SH2::GetLastXOffsets.begin(), SH2::GetLastXOffsets.end(), offset));

        switch (offsetItr) {
            case 0:
                if (NmsTextView_GetLastY() != store_Y1)
                    store_X1 = Orig();
                return store_X1;
            case 1: {
                int value = store_X1 + store_X2;
                store_X2 = 0;
                return value;
            }
            default:
                return Orig();
        }
    }
};

HOOK_DEFINE_TRAMPOLINE(PutCodeTo) {

    static char* Callback(void* _NMS_CTL_PARAM, unsigned char byte1, unsigned char byte2) {
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
            ((SjisToUtf8)(SJIStoUTF8_origin))(textBufferSJIS, 0x40, textBufferUTF8);
            store_X2 = getDrawTextWidth(textBufferUTF8, 1.0);
            free(textBufferSJIS);
            free(textBufferUTF8);
        }
        else if (Keyword) {
            if (byte1) {
                memcpy(textBufferSJIS+offset, &byte1, 1);
                offset += 1;
            }
            if (byte2) {
                memcpy(textBufferSJIS+offset, &byte2, 1);
                offset += 1;
            }
        }
        return Orig(_NMS_CTL_PARAM, byte1, byte2);
    }

};

HOOK_DEFINE_TRAMPOLINE(LoadModule) {

        static Result Callback(nn::ro::Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize, int flag) {

            Result ret = Orig(pOutModule, pImage, buffer, bufferSize, 1);
            uintptr_t pointer = 0;

            /* Hook function responsible for converting text between encodings
            to replace text in certain parts of game on the fly.*/
            
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13SJIStoUTF8_NXPKciPc");
            SJIStoUTF8::InstallAtPtr(pointer);
            SJIStoUTF8_origin = pointer;

            // Hook Yes/No Window to replace hardcoded text
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z20Wins_YesNoWindow_SetiiiPKcS0_");
            Wins_YesNoWindow::InstallAtPtr(pointer);
            
            // Hook DrawText to repair issue with rendering separated parts of text in one line
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z8DrawTextiiijPKcffi");
            DrawText::InstallAtPtr(pointer);
            
            // Hook GetLastX and PutCode to repair Ruby effect
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z20NmsTextView_GetLastXv");
            GetLastX::InstallAtPtr(pointer);

            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z16NmsCtl_PutCodeToP14_NMS_CTL_PARAMhh");
            PutCodeTo::InstallAtPtr(pointer);

            // Find symbol to determine NRO start pointer
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_ZN12clsNameInput16SetLastSelectStrEv");

            if (!strncmp(pOutModule->pathToNro, "nro/Tfoaf1.nro", strlen("nro/Tfoaf1.nro"))) {
                ShinHaya1_set = true;
                NRO_Tfoaf_start = pointer - 0x7000;
            }
            else {
                NRO_Tfoaf_start = pointer - 0x76E0;
            }
                
            return ret;
    }
};


extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    /* Install the hook at the provided function pointer. Function type is checked against the callback function. */
    CMojiFontDraw::InstallAtFuncPtr(_ZN4Nmpl9Framework7GraUtil13CMojiFontDrawC1ERNS1_9CMojiFontE);

    LoadModule::InstallAtFuncPtr(nn::ro::LoadModule);

    /* Alternative install funcs: */
    /* InstallAtPtr takes an absolute address as a uintptr_t. */
    /* InstallAtOffset takes an offset into the main module. */

    /*
    For sysmodules/applets, you have to call the entrypoint when ready
    exl::hook::CallTargetEntrypoint(x0, x1);
    */
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}