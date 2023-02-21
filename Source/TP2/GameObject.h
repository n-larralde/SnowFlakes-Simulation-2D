#pragma once

namespace SF
{
    class Player;

    class GameObject
    {
    public:
        GameObject();
        GameObject(double x, double y);

        virtual void update();
        virtual void render() const;
        void testCollision(Player&);

        virtual void initialize(double x, double y); // correspond au "new"
        virtual void clear(); // correspond au "delete"

        bool shouldDelete() const;
        bool isActive() const;

    protected:
        bool isColliding(const Player&) const;
        virtual void collide(Player&) = 0;

        double _x;
        double _y;
        double _w, _h;
        double _vx;
        double _vy;
        double _ax;
        double _ay;

        double _colorR, _colorG, _colorB, _colorA;
        bool _deleteMe;
        bool _isActive;
    };
}
