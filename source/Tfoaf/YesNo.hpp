#include "Tree.hpp"

std::array YesNo_data = {
    Text{"ここから再開しますか？", "Do you wish to resume the story from here?"}
};
std::span<Text> YesNo(YesNo_data);

uint64_t (*Wins_YesNoWindow_Set_original)(int unk0, int unk1, int unk2, const char* string1, const char* string2);