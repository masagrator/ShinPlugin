#pragma once
#include "main_patch.hpp"

std::vector<ptrdiff_t> NMSTextOffsets = {
    0x4E6A4, //Animated Text
    0x4EFAC, //Static Text
};

extern "C" {
    int64_t _Z16getDrawTextWidthPKcf(char const* Text, float scale);
}

uint64_t (*DrawText_original)(int w0, int w1, int w2, unsigned int w3, float s0, float s1, char const* Text, int w4);
