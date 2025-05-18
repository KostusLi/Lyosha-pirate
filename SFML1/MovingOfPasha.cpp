#include "MovingOfPasha.h"

void pashaMove(sf::RectangleShape& pashok, sf::Vector2f& moveRec)
{
    pashok.move(moveRec);
    sf::Vector2f pos = pashok.getPosition();
    if (pos.x > 1200) pashok.setPosition({ 1200, pos.y });
    if (pos.x < 50) pashok.setPosition({ 50, pos.y });
    if (pos.y > 670) pashok.setPosition({ pos.x, 670 });
    if (pos.y < 120) pashok.setPosition({ pos.x, 120 });

    if ((pos.x > 1200) && (pos.y < 120)) pashok.setPosition({ 1200, 120 });
    if ((pos.x > 1200) && (pos.y > 670)) pashok.setPosition({ 1200, 670 });
    if ((pos.x < 50) && (pos.y < 120)) pashok.setPosition({ 50, 120 });
    if ((pos.x < 50) && (pos.y > 670)) pashok.setPosition({ 50, 670 });
}

void Correct(Full& canister, int i, Meteor* meteor, int nmeteor)
{
    for (int i1 = 0; i1 < nmeteor; i1++)
    {
        if (i1 != i)
        {
            if (meteor[i1].collision(meteor[i].getMeteorBounds()))
            {
                meteor[i].restart();
                Correct(canister, i, meteor, nmeteor);
                break;
            }
        }
    }
    if (canister.collision(meteor[i].getMeteorBounds()))
    {
        meteor[i].restart();
        Correct(canister, i, meteor, nmeteor);
    }
}

void CorrectFull(Full& canister, Meteor* meteor, int nmeteor)
{
    for (int i1 = 0; i1 < nmeteor; i1++)
    {
        if (meteor[i1].collision(canister.getMeteorBounds()))
        {
            canister.restart();
            CorrectFull(canister, meteor, nmeteor);
            return;
        }
    }
}

string IntToStr(int number)
{
    ostringstream TextString;
    TextString << number;
    return TextString.str();
}