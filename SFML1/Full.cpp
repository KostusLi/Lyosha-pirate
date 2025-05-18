#include "Full.h"

Full::Full(std::filesystem::path name, int x, int y)
{
	TextureObject.loadFromFile(name);
	SpaceObject.setTexture(TextureObject);
	SpaceObject.setTextureRect(IntRect({ 0, 0 }, { x, y }));
	int scal = 1000 / x;
	SpaceObject.setScale({ 0.05f * scal, 0.05f * scal });
	restart();
}

Full::~Full()
{
}

void Full::restart()
{
	newBorn = true;
	float x = static_cast<float>(rand() % 1280 + 1280);
	float y = static_cast<float>(rand() % 540 + 130);

	SpaceObject.setPosition(Vector2f(x, y));
	PosBonus = SpaceObject.getPosition();
}