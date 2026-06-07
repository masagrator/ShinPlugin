#include "lib.hpp"
#include "nn/ro.h"
#include <span>
#include <algorithm>
#include "Tree.hpp"
#include "Logic.hpp"
#include "Phrase.hpp"
#include "YesNo.hpp"
#include "TextView_Render.hpp"
#include "xxHash/xxhash.h"
#include "textureHashes.hpp"
#include "nn/os.hpp"
#include <cmath>
#include "nn/util/util_gzip.hpp"
#include "nn/util/util_snprintf.hpp"
#include <unordered_map>

int countLSBZeros(int value) {
	unsigned int c = 0;
	while (((value >> c) & 1) == 0) {
		c++;
	}
	return c;
}

class Swizzler {
public:
	Swizzler() {}
	Swizzler(unsigned int width, unsigned int bpp, unsigned int blockHeight) {
		bhMask = (blockHeight * 8) - 1;

		bhShift = countLSBZeros(blockHeight * 8);
		bppShift = countLSBZeros(bpp);

		unsigned int widthInGobs = (unsigned int)ceil(width * bpp / 64.);

		gobStride = 512 * blockHeight * widthInGobs;
		xShift = countLSBZeros(blockHeight * 512);
	}

	unsigned int getOffset(unsigned int x, unsigned int y) {
		x <<= bppShift;

		unsigned int off = (y >> bhShift) * gobStride;
		off += (x >> 6) << xShift;
		off += ((y & bhMask) >> 3) << 9;
		off += ((x & 0x3F) >> 5) << 8;
		off += ((y & 0x07) >> 1) << 6;
		off += ((x & 0x1F) >> 4) << 5;
		off += ((y & 0x01) >> 0) << 4;
		off += ((x & 0x0F) >> 0) << 0;

		return off;
	}

	unsigned int bhMask;
	unsigned int bhShift;
	unsigned int bppShift;
	unsigned int gobStride;
	unsigned int xShift;
};

struct CMojiFont {
	char reserved[38];
	bool varWidth;
};

struct find_JPN {
	const char* JPN;
	find_JPN(const char* JPN) : JPN(JPN) {}
	bool operator () ( const Text& m ) const
	{
		return !memcmp(m.JPN, JPN, strlen(m.JPN)+1);
	}
};

uintptr_t NRO_Tfoaf_start = 0;
uint8_t ShinHaya_set = 0;
uintptr_t SJIStoUTF8_origin = 0;
uintptr_t UTF8toSJIS_origin = 0;
uintptr_t gpStartArchive = 0;

struct textureInfo {
    char reserved[200];
    int textureFormat;
};

// Define a dummy struct larger than 16 bytes to force X8 usage
struct DummyRetStruct {
    char dummy[24];
};

extern "C" {
	// This function has only one argument, but two more are used to fix issue with segfault
	void _ZN4Nmpl9Framework7GraUtil13CMojiFontDrawC1ERNS1_9CMojiFontE(CMojiFont* fontPtr, void* unk1, void* unk2);
    typedef void (*SjisToUtf8)(char const* src, int bufferSize, char* dst);
    typedef void (*Utf8ToSjis)(char const* src, int bufferSize, char* dst);
    void* _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(size_t size);
    void _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(void* buffer);
    void _ZN4Nmpl4Core9CCompress7autoDecEPvjRPhRjj(uint8_t* in_buffer, size_t com_size, void** out_buffer, uint32_t* unk, uint32_t unc_size);
    FILE* FDKfopen(const char * filename, const char * mode);
    int FDKfclose(FILE* stream);
    int FDKfprintf(FILE* stream, const char* format, ...);
    int FDKfseek(FILE* stream, int offset, int origin);
    int FDKfread(void* ptr, int size, int count, FILE* stream);
    int FDKfwrite(const void* ptr, int size, int count, FILE* stream);
    int FDKftell(FILE* stream);
    void cnov_swizzle_ram(void* out_buffer, void* in_buffer, uint powerOfTwoHeight, uint powerOfTwoWidth, void* unk1, void* unk2, uint bitsPerBlock);
    DummyRetStruct _ZN4Nmpl3Gra10CGraTexMgr7loadTexEPKvPKc(void* _this, void* texture, const char* in_filepath);
}

ptrdiff_t returnInstructionOffset(uintptr_t LR) {
	return LR - NRO_Tfoaf_start;
}

HOOK_DEFINE_TRAMPOLINE(CMojiFontDraw) {

    static void Callback(CMojiFont* fontPtr, void* unk1, void* unk2) {

        Orig(fontPtr, unk1, unk2);
        fontPtr -> varWidth = true;
    }

};

bool ReplaceSJIStoUTF8(std::span<Text> Vector, char* dst, int bufferSize, std::span<Text>::iterator itr) {
	if (itr != Vector.end() && strlen(itr->ENG) <= (size_t)bufferSize) {
        if (!strlen(itr->ENG))
            return false;
		memcpy(dst, itr->ENG, strlen(itr->ENG));
		return true;
	}
    return false;
}

HOOK_DEFINE_TRAMPOLINE(SJIStoUTF8) {

    static void Callback(char const* src, int bufferSize, char* dst) {
        ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));

        if (ShinHaya_set == 1) {
            if (offset == SH1::LogicOffset || offset == SH1::LogicGetHelp) {
                char* checkJPN = (char*)calloc(1, bufferSize);
                Orig(src, bufferSize, checkJPN);

                auto it = std::find_if(SH1::Logic.begin(), SH1::Logic.end(), find_JPN(checkJPN));
                if (!ReplaceSJIStoUTF8(SH1::Logic, dst, bufferSize, it))
                    Orig(src, bufferSize, dst);
                
                free(checkJPN);
                return;
            }
            else if (offset == SH1::LogicDescriptionsOffset) {
                char* checkJPN = (char*)calloc(1, bufferSize);
                Orig(src, bufferSize, checkJPN);
                
                auto it = std::find_if(SH1::LogicDescriptions.begin(), SH1::LogicDescriptions.end(), find_JPN(checkJPN));
                if (!ReplaceSJIStoUTF8(SH1::LogicDescriptions, dst, bufferSize, it))
                    Orig(src, bufferSize, dst);
                
                free(checkJPN);
                return;
            }
            else if (offset == SH1::FOAF_popup_offset) {
                char* checkJPN = (char*)calloc(1, bufferSize);
                Orig(src, bufferSize, checkJPN);
                if (!strncmp("…", checkJPN, sizeof("…")))
                    Orig("...", bufferSize, dst);
                else Orig(src, bufferSize, dst);
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
                        if (!ReplaceSJIStoUTF8(SH1::Tree2C, dst, bufferSize, 
                            std::find_if(SH1::Tree2C.begin(), SH1::Tree2C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 1:
                        if (!ReplaceSJIStoUTF8(SH1::Tree4C, dst, bufferSize, 
                            std::find_if(SH1::Tree4C.begin(), SH1::Tree4C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 2:
                        if (!ReplaceSJIStoUTF8(SH1::Tree8C, dst, bufferSize, 
                            std::find_if(SH1::Tree8C.begin(), SH1::Tree8C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 3:
                        if (!ReplaceSJIStoUTF8(SH1::TreeCC, dst, bufferSize, 
                            std::find_if(SH1::TreeCC.begin(), SH1::TreeCC.end(), find_JPN(checkJPN))))
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

                if (!ReplaceSJIStoUTF8(SH2::Logic, dst, bufferSize,
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
                        if (!ReplaceSJIStoUTF8(SH2::Tree2C, dst, bufferSize, 
                            std::find_if(SH2::Tree2C.begin(), SH2::Tree2C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 1:
                        if (!ReplaceSJIStoUTF8(SH2::Tree6C, dst, bufferSize, 
                            std::find_if(SH2::Tree6C.begin(), SH2::Tree6C.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 2:
                        if (!ReplaceSJIStoUTF8(SH2::TreeAC, dst, bufferSize, 
                            std::find_if(SH2::TreeAC.begin(), SH2::TreeAC.end(), find_JPN(checkJPN))))
                            Orig(src, bufferSize, dst);
                        break;
                    case 3:
                        if (!ReplaceSJIStoUTF8(SH2::TreeEC, dst, bufferSize, 
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
            if (std::distance(YesNo.begin(), itr1) == 2 && string2) ((char*)(string2))[0] = 0;
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

        if (ShinHaya_set == 1) {
            if (std::find(SH1::NMSTextOffsets.begin(), SH1::NMSTextOffsets.end(), offset) != SH1::NMSTextOffsets.end()) {
                static int Old_X = 0;
                static int Old_Y = 0;
                static int64_t OldText_width = 0;

                if ((Pos_X > Old_X) && (Old_Y == Pos_Y)) {
                    Pos_X = store_X1;
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
                Pos_X = store_X1;
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

HOOK_DEFINE_TRAMPOLINE(DrawIcon) {
    static void Callback(WinsIcon iconID, int Pos_X, int Pos_Y, int unk, float Scale, uint RGBA) {
        ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));
        if (ShinHaya_set == 1 && offset != 0x4EA94) {
            return Orig(iconID, Pos_X, Pos_Y, unk, Scale, RGBA);
        }
        if (ShinHaya_set == 2) {
            return Orig(iconID, Pos_X, Pos_Y, unk, Scale, RGBA);
        }
        int width = Wins_GetIconWidth(iconID, (int)(Scale * 100));
        store_X1 += width / 2;
        Pos_X = store_X1;
        Orig(iconID, Pos_X, Pos_Y, unk, Scale, RGBA);
        store_X1 += width / 2;
    }
};

int Backlog_LastX = 0;
int Backlog_LastY = 0;

HOOK_DEFINE_TRAMPOLINE(DrawSystemText) {
    static void Callback(int Pos_X, int Pos_Y, int Pos_Z, unsigned int w3, float Scale, char const* Text) {
        ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));
        if (ShinHaya_set == 1) {
            switch(offset) {
                case 0x4D5C: //Backlog
                case 0x4EBC: //Backlog
                case 0x5048: //Backlog {
                    if (Pos_Y != Backlog_LastY) {
                        Backlog_LastY = Pos_Y;
                        Backlog_LastX = Pos_X;
                    }
                    else Pos_X = Backlog_LastX;
                    Orig(Pos_X, Pos_Y, Pos_Z, w3, Scale, Text);
                    Backlog_LastX += getDrawTextWidth(Text, Scale);
                    return;
            }
        }
        return Orig(Pos_X, Pos_Y, Pos_Z, w3, Scale, Text);
    }
};

HOOK_DEFINE_TRAMPOLINE(DrawIconForBacklog) {
    static void Callback(WinsIcon iconID, int Pos_X, int Pos_Y, int unk, float Scale, uint RGBA) {
        if (Pos_Y != Backlog_LastY) {
            Backlog_LastY = Pos_Y;
            Backlog_LastX = Pos_X;
        }
        int width = Wins_GetIconWidth(iconID, (int)(Scale * 100));
        Pos_X = Backlog_LastX;
        Orig(iconID, Pos_X, Pos_Y, unk, Scale, RGBA);
        Backlog_LastX += width;
    }
};

HOOK_DEFINE_TRAMPOLINE(GetLastX) {

    static int32_t Callback(void) {
        ptrdiff_t offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));
        auto offsetItr = -1;

        if (ShinHaya_set == 1) {
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

std::unordered_map<std::string, void*> loadedTextures;

HOOK_DEFINE_TRAMPOLINE(LoadTex) {

    static DummyRetStruct Callback(void* _this, void* texture, const char* in_filepath) {
        std::string name = in_filepath;
        name = name.substr(0, name.find(".nltx"));
        char filepath[128] = "";
        nn::fs::FileHandle filehandle;

        if (ShinHaya_set == 1) {
            nn::util::SNPrintf(filepath, sizeof(filepath), "rom0:/Tfoaf1/Textures/%s.tga.gz", name.c_str());
        }
        else if (ShinHaya_set == 2) {
            nn::util::SNPrintf(filepath, sizeof(filepath), "rom0:/Tfoaf2/Textures/%s.tga.gz", name.c_str());
        }
        if (strlen(filepath) != 0) {
            auto it = loadedTextures.find(filepath);
            if (it != loadedTextures.end()) {
                texture = it->second;
            }
            else if (R_SUCCEEDED(nn::fs::OpenFile(&filehandle, filepath, nn::fs::OpenMode_Read))) {
                long com_size = 0;
                nn::fs::GetFileSize(&com_size, filehandle);
                void* com_buffer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(com_size);
                nn::fs::ReadFile(filehandle, 0, com_buffer, com_size);
                nn::fs::CloseFile(filehandle);
                size_t in_size = nn::util::GetGzipDecompressedSize(com_buffer, com_size);
                void* in_buffer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(in_size);
                char workBuffer[nn::util::DecompressGzipWorkBufferSize] = "";
                if (nn::util::DecompressGzip(in_buffer, in_size, com_buffer, com_size, (void*)workBuffer, sizeof(workBuffer))) {
                    texture = in_buffer;
                    loadedTextures[std::string(filepath)] = in_buffer;
                }
                else _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(in_buffer);
                _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(com_buffer);
            }
            else {
                filepath[strlen(filepath)-3] = 0;
                auto it = loadedTextures.find(filepath);
                if (it != loadedTextures.end()) {
                    texture = it->second;
                }
                else if (R_SUCCEEDED(nn::fs::OpenFile(&filehandle, filepath, nn::fs::OpenMode_Read))) {
                    long in_size = 0;
                    nn::fs::GetFileSize(&in_size, filehandle);
                    void* in_buffer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(in_size);
                    nn::fs::ReadFile(filehandle, 0, in_buffer, in_size);
                    nn::fs::CloseFile(filehandle);
                    texture = in_buffer;
                    loadedTextures[std::string(filepath)] = in_buffer;
                }
            }
        }
        return Orig(_this, texture, filepath);
    }
};

bool ReplaceTexture(void** TexturePointer, uint16_t index, size_t texture_size, uint* width, uint* height, bool* isSwizzled) {

		char filepath[128] = "";
        if (!ShinHaya_set) {
            nn::util::SNPrintf(&filepath[0], 128, "rom0:/Textures/%04d.dds.gz", index);
        }
        else if (ShinHaya_set == 1) {
		    nn::util::SNPrintf(&filepath[0], 128, "rom0:/Tfoaf1/Textures/anm0/%04d.dds.gz", index);
        }
        else if (ShinHaya_set == 2) {
		    nn::util::SNPrintf(&filepath[0], 128, "rom0:/Tfoaf2/Textures/anm0/%04d.dds.gz", index);
        }

        FILE* tex = FDKfopen(filepath, "rb");
        if (tex) {
            FDKfseek(tex, 0, 2);
            long com_size = FDKftell(tex);
            FDKfseek(tex, 0, 0);
            void* com_buffer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(com_size);
            FDKfread(com_buffer, com_size, 1, tex);
            FDKfclose(tex);
            
            size_t in_size = nn::util::GetGzipDecompressedSize(com_buffer, com_size);
            *TexturePointer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(in_size);
            if (!*TexturePointer) {
                _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(com_buffer);
                return false;
            }
            char workBuffer[nn::util::DecompressGzipWorkBufferSize] = "";
            if (!nn::util::DecompressGzip(*TexturePointer, in_size, com_buffer, com_size, (void*)workBuffer, sizeof(workBuffer))) {
                _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(com_buffer);
                _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(*TexturePointer);
                return false;
            }
            _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(com_buffer);

            uint8_t* buffer = (uint8_t*)*TexturePointer;
            memcpy((void*)width, (void*)&buffer[0xC], 4);
            memcpy((void*)height, (void*)&buffer[0x10], 4);
            memcpy((void*)isSwizzled, (void*)&buffer[0x40], 1);
            uint32_t type = 0;
            memcpy((void*)&type, (void*)&buffer[0x54], 4);
            memcpy((void*)buffer, (void*)&buffer[((type == 0x30315844) ? 0x94 : 0x80)], *width * *height);
            return true;
        }
        else {
            filepath[strlen(filepath)-3] = 0;
            tex = FDKfopen(filepath, "rb");
            if (tex) {
                *TexturePointer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(texture_size);
                FDKfseek(tex, 0xC, 0);
                FDKfread(width, 4, 1, tex);
                FDKfread(height, 4, 1, tex);
                FDKfseek(tex, 0x40, 0);
                FDKfread(isSwizzled, 1, 1, tex);
                FDKfseek(tex, 0x54, 0);
                uint32_t type = 0;
                FDKfread(&type, 4, 1, tex);
                FDKfseek(tex, ((type == 0x30315844) ? 0x94 : 0x80), 0);
                FDKfread(*TexturePointer, texture_size, 1, tex);
                FDKfclose(tex);
                return true;
            }
        }
        return false;
}

//#define mutex_on

#ifdef mutex_on
nn::os::MutexType _mutex;
#endif

std::unordered_map<XXH64_hash_t, void*> textures;

HOOK_DEFINE_TRAMPOLINE(Decompress) {
    static void Callback(uint8_t* in_buffer, size_t com_size, void** out_buffer, uint32_t* unk, uint32_t unc_size) {
        #ifdef mutex_on
        nn::os::LockMutex(&_mutex);
        #endif
        if (unc_size == 0xFFFFFFFF) //This is used for saves
            return Orig(in_buffer, com_size, out_buffer, unk, unc_size);
        XXH64_hash_t hash_output = XXH3_64bits((void*)in_buffer, ((com_size < 0x1000) ? com_size : 0x1000));
        auto index = compareHashes0(hash_output);
        if (ShinHaya_set) index = compareHashes1(hash_output);
        if (index.hash == hash_output) {
            auto texture = textures.find(index.hash);
            if (texture != textures.end()) {
                *out_buffer = texture->second;
                return;
            }
            uint width = 0;
            uint height = 0;
            bool isSwizzled = false;
            if (ReplaceTexture(out_buffer, index.fileID, unc_size, &width, &height, &isSwizzled)) {
                if (isSwizzled) return;
                unsigned int swWidth = width;
                unsigned int swHeight = height;
                if (index.swizzleExpand > 0 && index.swizzleType >= 3 && index.bytesPerPixel != 4) {
                    swWidth = (index.swizzleExpand * 64) * (uint32_t)ceil((double)swWidth / (index.swizzleExpand * 64));
                    swHeight = (index.swizzleExpand * 64) * (uint32_t)ceil((double)swHeight / (index.swizzleExpand * 64));
                }
                if (index.bytesPerPixel > 4) {
                    width /= (index.bytesPerPixel / 4);
                    height /= (index.bytesPerPixel / 4);
                    swWidth /= (index.bytesPerPixel / 4);
                    swHeight /= (index.bytesPerPixel / 4);
                }
                Swizzler sw = Swizzler(swWidth, index.bytesPerPixel, pow(2, index.swizzleType));
                uint8_t* temp_buffer = (uint8_t*)*out_buffer;
                size_t new_size = swWidth * swHeight * index.bytesPerPixel;
                *out_buffer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(new_size);
                if (!*out_buffer) {
                    //Memory leak
                    _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(temp_buffer);
                    return Orig(in_buffer, com_size, out_buffer, unk, unc_size);
                }
                memset(*out_buffer, 0, new_size);
                size_t offset = 0;
                for (unsigned int y = 0; y < height; y++) {
		            for (unsigned int x = 0; x < width; x++) {
                        unsigned int off = sw.getOffset(x, y);
                        memcpy((void*)&((uint8_t*)*out_buffer)[off], &temp_buffer[offset], index.bytesPerPixel);
                        offset += index.bytesPerPixel;
                    }
                }

                _ZN4Nmpl4Core6Memory9CGmemHeap4freeEPv(temp_buffer);
                #ifdef mutex_on
                nn::os::UnlockMutex(&_mutex);
                #endif
                return;
            }
            
        }
        #ifdef mutex_on
        nn::os::UnlockMutex(&_mutex);
        #endif
        return Orig(in_buffer, com_size, out_buffer, unk, unc_size);
    }
};

uintptr_t tfoaf1_font_system_ptr = 0;

HOOK_DEFINE_INLINE(ReplaceFont) {

    static void Callback(exl::hook::nx64::InlineCtx* ctx) {
        if (ShinHaya_set == 1) {
            XXH64_hash_t hash_output = XXH3_64bits((void*)(ctx->X[21]), 0x1000);
            switch(hash_output) {
                case 0x9091F51A7F73450Clu:
                    if (tfoaf1_font_system_ptr) {
                        ctx->X[21] = tfoaf1_font_system_ptr;
                        ctx -> W[8] = *(uint16_t*)(ctx -> X[21]);
                        return;
                    }
                    FILE* tex = FDKfopen("rom0:/Tfoaf1/font_system.bin", "rb");
                    if (!tex) {
                        ctx -> W[8] = *(uint16_t*)(ctx -> X[21]);
                        return;
                    }
                    FDKfseek(tex, 0, 2);
                    int new_size = FDKftell(tex);
                    FDKfseek(tex, 0, 0);
                    if (new_size > 5031598) {
                        void* buffer = _ZN4Nmpl4Core6Memory9CGmemHeap6mallocEm(new_size);
                        ctx->X[21] = (u64)buffer;
                    }
                    tfoaf1_font_system_ptr = ctx->X[21];
                    FDKfread((void*)ctx->X[21], new_size, 1, tex);
                    FDKfclose(tex);
            }
        }
        ctx -> W[8] = *(uint16_t*)(ctx -> X[21]);
    }
};

HOOK_DEFINE_TRAMPOLINE(PhraseCtlFunc) {
    static void Callback(void) {
        ptrdiff_t base = NRO_Tfoaf_start + 0x11E00C4;
        ptrdiff_t offset = 108;
        if (ShinHaya_set == 2) {
            base = 0;
            offset = 0;
        }
        for (size_t i = 0; i < 32; i++) {
            char* sjis_string = (char*)(base + (offset * i));
            size_t len = strlen(sjis_string);
            if (len > 1) {
                char* checkJPN = (char*)calloc(1, 0x40);
                ((SjisToUtf8)(SJIStoUTF8_origin))(sjis_string, 0x40, checkJPN);
                auto itr = std::find_if(SH1::PhraseCtl.begin(), SH1::PhraseCtl.end(), find_JPN(checkJPN));
                free(checkJPN);
                if (itr != SH1::PhraseCtl.end()) {
                    memset(sjis_string, 0, 0x40);
                    ((Utf8ToSjis)(UTF8toSJIS_origin))(SH1::PhraseCtl[std::distance(SH1::PhraseCtl.begin(), itr)].ENG, 0x40, sjis_string);
                }

            }

        }
        return Orig();
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

            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13UTF8toSJIS_NXPKciPc");
            UTF8toSJIS_origin = pointer;

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

            //Fix drawing icons in Backlog
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z23Wins_DrawIconForBackLog8WinsIconiiifj");
            DrawIconForBacklog::InstallAtPtr(pointer);

            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z14DrawSystemTextiiijPKcf");
            DrawSystemText::InstallAtPtr(pointer);

            //Fix drawing icons in Messages
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z13Wins_DrawIcon8WinsIconiiifj");
            DrawIcon::InstallAtPtr(pointer);

            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_Z16PhraseCtl_Renderv");
            PhraseCtlFunc::InstallAtPtr(pointer);
            

            // Find symbol to determine NRO start pointer
            nn::ro::LookupModuleSymbol(&pointer, pOutModule, "_ZN12clsNameInput16SetLastSelectStrEv");

            if (!strncmp(pOutModule->pathToNro, "nro/Tfoaf1.nro", strlen("nro/Tfoaf1.nro"))) {
                ShinHaya_set = 1;
            }
            else {
                ShinHaya_set = 2;
            }
            MemoryInfo meminfo;
            u32 dummy;
            svcQueryMemory(&meminfo, &dummy, pointer);
            NRO_Tfoaf_start = meminfo.addr;
                
            return ret;
    }
};

namespace nn::fs {
    /*
        If not set to true, instead of returning result with error code
        in case of any fs function failing, Application will abort.
    */
    Result SetResultHandledByApplication(bool enable);
};


extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    /* Install the hook at the provided function pointer. Function type is checked against the callback function. */
    CMojiFontDraw::InstallAtFuncPtr(_ZN4Nmpl9Framework7GraUtil13CMojiFontDrawC1ERNS1_9CMojiFontE);

    LoadModule::InstallAtFuncPtr(nn::ro::LoadModule);

    nn::fs::SetResultHandledByApplication(true);

    //LoadTex_start::InstallAtOffset(0x444F4);
    LoadTex::InstallAtFuncPtr(_ZN4Nmpl3Gra10CGraTexMgr7loadTexEPKvPKc);

    Decompress::InstallAtFuncPtr(_ZN4Nmpl4Core9CCompress7autoDecEPvjRPhRjj);

    ReplaceFont::InstallAtOffset(0x6FA7C);

    #ifdef mutex_on
    memset(&_mutex, 0, sizeof(_mutex));
    nn::os::InitializeMutex(&_mutex, false, 1);
    #endif

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