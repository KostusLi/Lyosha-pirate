#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Meteor
{
public:
    Meteor();
    ~Meteor();

    void move(float& time);
    void draw(RenderWindow& window);
    bool collision(FloatRect object);
    virtual void restart();
    const FloatRect getMeteorBounds();
    bool newBorn;

    Vector2f getPosBonus()
    {
        return PosBonus;
    }

protected:
    Sprite SpaceObject;
    Texture TextureObject;
    Vector2f PosBonus;

private:
    int xsp[5]{ 3, 73, 135, 198, 262 };
    int ysp[6]{ 3, 68, 132, 200, 265, 325 };
    int ix, iy = 0;
    int st = 0;
};