#pragma once

namespace SH1 {
    std::array NMSTextOffsets = {
        0x37C80, //Select
        0x387A0, //After Select
        0x46F94, //FOAF popup
        0x4E6A4, //Animated Text
        0x4EFAC  //Static Text
    };

    // Those offsets are used for Ruby to calculate middle of text
    std::array GetLastXOffsets = {
        0x46128, // Keyword Start
        0x46298 // Keyword End
    };
}

namespace SH2 {
    std::array NMSTextOffsets = {
        0x3CFBC, //Select
        0x3DBB0, //After Select
        0x4E494, //FOAF popup
        0x53184, //Animated Text
        0x53A8C  //Static Text
    };

    // Those offsets are used for Ruby to calculate middle of text
    std::array GetLastXOffsets = {
        0x4BD18, // Keyword Start
        0x4BE88 // Keyword End
    };
}

enum WinsIcon {
    dummy = 0,
    dummy1 = 1,
    Courage = 0x10
};

int64_t getDrawTextWidth(char const* Text, float scale);
int32_t NmsTextView_GetLastY(void);
int32_t Wins_GetIconWidth(WinsIcon iconId, int scaleInPercent);