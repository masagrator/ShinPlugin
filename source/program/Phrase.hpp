#pragma once

#include "Tree.hpp"

namespace SH1 {
    std::array PhraseCtl_data = {
        Text("【検証１】", "[To Verify 1] "),
        Text("【検証２】", "[To Verify 2] "),
        Text("【検証３】", "[To Verify 3] ")
    };

    std::span<Text> PhraseCtl(PhraseCtl_data);
}