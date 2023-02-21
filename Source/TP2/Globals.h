#pragma once

#include <array>

namespace SF
{
    using uchar = unsigned char;
    using uint = unsigned int;

    using ulong = unsigned long;
    using PresetList = std::array<ulong, 9>;
    inline static const PresetList _presets = { 5000, 50000, 75000, 100000, 150000, 200000, 300000, 400000, 500000 };

    static const char* WINDOW_TITLE = "Snow simulator";
    const int SCREEN_WIDTH  = 720;
    const int SCREEN_HEIGHT = 480;
    const uint FPS = 30;
}
