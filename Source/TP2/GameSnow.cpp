#include <iostream>
#include <raylib.h>
#include <Code_Utilities_Light_v2.h>
#include <memory>

#include "Globals.h"
#include "GameSnow.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"
#include "SnowflakePool.h"

using namespace std;
using namespace SF;

GameSnow::GameSnow() 
    : _pause(false)
    , _p(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
{
    cout << "Player size: " << sizeof(Player) << endl;
    cout << "GameObject size: " << sizeof(GameObject) << endl;
    cout << "Snowflake size: " << sizeof(Snowflake) << endl;
    cout << "SnowflakeNoContact size: " << sizeof(SnowflakeNoContact) << endl;
    cout << "SnowflakeRebound size: " << sizeof(SnowflakeRebound) << endl;
    cout << "SnowflakeSine size: " << sizeof(SnowflakeSine) << endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS); // Set our game to run at 30 frames-per-second
    init(_presets[0]);

    BdB::srandInt((uint)time(0));
}

GameSnow::~GameSnow()
{
    CloseWindow();
}

void GameSnow::init(uint n)
{
    cout << "Init with " << n << " particles" << endl;

    _sfPool.reset();
    _sfncPool.reset();
    _sfrPool.reset();
    _sfsPool.reset();

    for (uint i{}; i<n; ++i)
        addSnowflake(BdB::randInt(SCREEN_WIDTH), BdB::randInt(SCREEN_HEIGHT));
}

void GameSnow::addSnowflake()
{
    // Default : top of the screen
    addSnowflake(BdB::randInt(SCREEN_WIDTH), -10);
}

void GameSnow::addSnowflake(double x, double y)
{
    int rnd = BdB::randInt(RAND_MAX);
    if(rnd < RAND_MAX / 10)
        _sfrPool.spawn(x, y);
    else if(rnd < RAND_MAX / 5 * 2)
        _sfncPool.spawn(x, y);
    else if(rnd < RAND_MAX / 2)
        _sfsPool.spawn(x, y);
    else
        _sfPool.spawn(x, y);
}

int GameSnow::getClickX()
{
    return std::clamp(GetMouseX(), 0, SCREEN_WIDTH);
}

int GameSnow::getClickY()
{
    return std::clamp(GetMouseY(), 0, SCREEN_HEIGHT);
}

void GameSnow::handleInput()
{
    // Mouse
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
       _p.setPosition(GetMouseX(), GetMouseY());

    // Direction pressed
    _p.setDirection(
        IsKeyDown(KeyboardKey::KEY_LEFT),
        IsKeyDown(KeyboardKey::KEY_RIGHT),
        IsKeyDown(KeyboardKey::KEY_DOWN),
        (IsKeyDown(KeyboardKey::KEY_UP) || IsKeyDown(KeyboardKey::KEY_SPACE))
    );

    // Key pressed
    int key = GetKeyPressed();
    switch (key)
    {
            // Pause
        case KeyboardKey::KEY_P:            
            _pause = !_pause;// Pause
            break;
        case KeyboardKey::KEY_ESCAPE:
            _keepPlaying = false;
            break;

        // Number of particles
        case KeyboardKey::KEY_KP_1:
        case KeyboardKey::KEY_KP_2:
        case KeyboardKey::KEY_KP_3:
        case KeyboardKey::KEY_KP_4:
        case KeyboardKey::KEY_KP_5:
        case KeyboardKey::KEY_KP_6:
        case KeyboardKey::KEY_KP_7:
        case KeyboardKey::KEY_KP_8:
        case KeyboardKey::KEY_KP_9:
            init(_presets[key - KeyboardKey::KEY_KP_1]);
            break;
    }
}

void GameSnow::update()
{
    if (_pause) 
        return;

    //double delta_t = dt / 1000.0;

    // Physics
    _p.update();

    // UPDATE
    _sfPool.update();
    _sfncPool.update();
    _sfrPool.update();
    _sfsPool.update();

    // Collisions
    _sfPool.collisions(_p);
    _sfncPool.collisions(_p);
    _sfrPool.collisions(_p);
    _sfsPool.collisions(_p);

    // Replace inactive snowflakes
    size_t nb_new_snowflakes = _sfPool.destroy() + _sfncPool.destroy() + _sfrPool.destroy() + _sfsPool.destroy();
    for (uint i{}; i < nb_new_snowflakes; ++i)
        addSnowflake();
}

void GameSnow::render() const
{
    BeginDrawing();
    {
        ClearBackground(BLANK);
        _p.render();

        for (uint i{}; i < _sfPool.getNbSnowflakes(); ++i)
            _sfPool.get(i).render();

        for (uint i{}; i < _sfrPool.getNbSnowflakes(); ++i)
            _sfrPool.get(i).render();

        for (uint i{}; i < _sfsPool.getNbSnowflakes(); ++i)
            _sfsPool.get(i).render();

        for (uint i{}; i < _sfncPool.getNbSnowflakes(); ++i)
            _sfncPool.get(i).render();

        DrawFPS(20, 20);
    }
    EndDrawing();
}
