#pragma once

#include <array>

namespace SF
{
    using uchar = unsigned char;
    using uint = unsigned int;

    using ulong = unsigned long;
    using PresetList = std::array<ulong, 9>;
    inline static const PresetList _presets = { 470000, 480000, 490000, 500000, 510000, 520000, 530000, 540000, 550000 };

    static const char* WINDOW_TITLE = "Snow simulator";
    const int SCREEN_WIDTH  = 720;
    const int SCREEN_HEIGHT = 480;
    const uint FPS = 30;
}
