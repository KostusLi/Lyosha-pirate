#pragma once
#include "Meteor.h"
#include <filesystem>

class Full : public Meteor
{
public:
    Full(std::filesystem::path name, int x, int y);
    ~Full();
    virtual void restart();
};