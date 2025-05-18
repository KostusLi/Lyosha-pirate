#include "Meteor.h"

Meteor::Meteor() : SpaceObject(TextureObject)
{
    TextureObject.loadFromFile("images/Lesha.jpg");
    SpaceObject.setTextureRect(IntRect({ 0, 0 }, { 101, 98 }));
    restart();
}

Meteor::~Meteor()
{
}

void Meteor::draw(RenderWindow& window)
{
    window.draw(SpaceObject);
}

void Meteor::move(float& time)
{
    newBorn = false;
    SpaceObject.move({ static_cast<float>(-0.5 * time), 0 });
    PosBonus = SpaceObject.getPosition();
    if (SpaceObject.getPosition().x < -60) restart();
}

bool Meteor::collision(FloatRect object)
{
    if (SpaceObject.getGlobalBounds().findIntersection(object)) return true;
    return false;
}

void Meteor::restart()
{
    newBorn = true;
    float s = static_cast<float>(rand() % 15+10);
    float x = static_cast<float>(rand() % 1280 + 1280);
    float y = static_cast<float>(rand() % 540 + 130);

    SpaceObject.setPosition(Vector2f(x, y));
    SpaceObject.setScale({ s / 20, s / 20 });
    ix = rand() % 4;
    iy = rand() % 5;
    st = rand() % 2;

    PosBonus = SpaceObject.getPosition();
}

const FloatRect Meteor::getMeteorBounds()
{
    return SpaceObject.getGlobalBounds();
}