#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "GameObject.h"
#include "Player.h"

using namespace SF;

GameObject::GameObject()
    : _x{}, _y{}
    , _w{}, _h{}
    , _vx{ 0 }, _vy{ 0 }, _ax{ 0 }, _ay{ 0 }
    , _colorR{}, _colorG{}, _colorB{}, _colorA{}
    , _deleteMe{false}
    , _isActive{false}
{}

GameObject::GameObject(double x, double y) 
    : _x{x}, _y{y}
    , _w{}, _h{}
    , _vx{0}, _vy{0}, _ax{0}, _ay{0}
    , _colorR{}, _colorG{}, _colorB{}, _colorA{}
    , _deleteMe{false}
    , _isActive{false}
{}

void GameObject::update()
{
	float dt = GetFrameTime();
    _vx += dt * _ax;
    _vy += dt * _ay;

    _x += dt * _vx;
    _y += dt * _vy;
}

void GameObject::render() const
{
    Color c
    { 
       (uchar) (_colorR * 255),
       (uchar) (_colorG * 255),
       (uchar) (_colorB * 255),
       (uchar) (_colorA * 255)
    };

    Rectangle r{};
    r.x         = (float) _x;
    r.y         = (float) _y;
    r.width     = (float) _w;
    r.height    = (float) _h;

    DrawRectangleRec(r, c);
}

void GameObject::testCollision(Player& p)
{
    if (isColliding(p))
        collide(p);
}

bool GameObject::isColliding(const Player& p) const
{
    bool pRightVSmeLeft = p._x + p._w < _x;
    bool meRightVSpLeft = _x + _w < p._x;
    bool pBottomVSmeTop = p._y + p._h < _y;
    bool meBottomVSpTop = _y + _h < p._y;

    return !(
        // Un à gauche de l'autre
        pRightVSmeLeft ||
        meRightVSpLeft ||
        // Un en haut de l'autre
        pBottomVSmeTop ||
        meBottomVSpTop);
}

void GameObject::initialize(double x, double y)
{
    _x = x;
    _y = y;
    _isActive = true;
    _deleteMe = false;
}

void GameObject::clear()
{
    _isActive = false;
    _deleteMe = true;
}

bool GameObject::shouldDelete() const
{
    return _deleteMe;
}

bool SF::GameObject::isActive() const
{
    return _isActive;
}
