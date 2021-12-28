#pragma once
#include "main_patch.hpp"

std::vector<ptrdiff_t> NMSTextOffsets = {
    0x4E6A4, //Animated Text
    0x4EFAC, //Static Text
    0x37C80  //Select

};

// Those offsets are used for Ruby to calculate middle of text
std::vector<ptrdiff_t> GetLastXOffsets = {
    0x46128, // Keyword Start
    0x46298 // Keyword End
};

int64_t getDrawTextWidth(char const* Text, float scale);
int32_t NmsTextView_GetLastY(void);

uint64_t (*DrawText_original)(int w0, int w1, int w2, unsigned int w3, float s0, float s1, char const* Text, int w4);
char* (*PutCodeTo_original)(void* _NMS_CTL_PARAM, unsigned char byte1, unsigned char byte2);