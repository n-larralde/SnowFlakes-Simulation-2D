#include <raylib.h>
#include <Code_Utilities_Light_v2.h>
#include <cmath>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeSine.h"

using namespace SF;

SnowflakeSine::SnowflakeSine()
    : Snowflake{}
{
    _timeSinceStart = BdB::randInt(RAND_MAX) / (double)RAND_MAX * 2 * PI;
}

void SnowflakeSine::update() 
{
    float dt = GetFrameTime();
    _timeSinceStart += dt;

    _vx = 50 * sin(3 * _timeSinceStart);

    Snowflake::update();
}
