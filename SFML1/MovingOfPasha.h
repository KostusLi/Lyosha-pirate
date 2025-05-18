#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <string>
#include "Meteor.h"
#include "Full.h"
using namespace std;
using namespace sf;

struct FrameAnim
{
    int Frame = 0;
    int Step = 100;
    int Frame1 = 0;
    int Step1 = 100;
};

void pashaMove(sf::RectangleShape& pashok, sf::Vector2f& moveRec);
void Correct(Full& canister, int i, Meteor* meteor, int nmeteor);
void CorrectFull(Full& canister, Meteor* meteor, int nmeteor);
string IntToStr(int number);