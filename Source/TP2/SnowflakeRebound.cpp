#include <iostream>
#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"

using namespace std;
using namespace SF;

SnowflakeRebound::SnowflakeRebound()
    : Snowflake{}
    , _alreadyHit{false}
{
    _h = 2;
    _w = 2;
    _colorA = 1;
    _vx = BdB::randInt(RAND_MAX) < RAND_MAX / 2 ? -30 : 30;
}

void SnowflakeRebound::update()
{
    Snowflake::update();

    if (_x < _w || _x > SCREEN_WIDTH + _w) 
    {
        _deleteMe = true;
        return;
    }

    if (_y + _h > SCREEN_HEIGHT && !_alreadyHit) 
        rebound();
    else if (_y > SCREEN_HEIGHT + _h && _alreadyHit) 
        _deleteMe = true;
}

void SnowflakeRebound::collide(Player&)
{
    if (!_alreadyHit)
        rebound();
    else
        _deleteMe = true;
}

void SnowflakeRebound::rebound()
{
    _vy *= -1;
    _ay = 300;
    _alreadyHit = true;
}
