#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <filesystem>
#include "MovingOfPasha.h"
using namespace std;

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), L"Лёха-пират", sf::State::Fullscreen);

    auto icon = sf::Image{};
    if (!icon.loadFromFile("images/icon.png"))
    {
        cerr << "Failed to load images/icon.png" << endl;
        return 2;
    }
    window.setIcon(icon.getSize(), icon.getPixelsPtr());

    bool mus = false;
    sf::Music gameMusic("music/hole.mp3");
    gameMusic.setVolume(70.f);
    gameMusic.setLooping(true);

    sf::SoundBuffer fal, bufM, bufB, vic;
    fal.loadFromFile("music/suka.mp3");
    bufM.loadFromFile("music/chin.mp3");
    bufB.loadFromFile("music/daa.mp3");
    vic.loadFromFile("music/chiki.mp3");
    sf::Sound falsound(fal), soundbonM(bufM), soundbonB(bufB), soundvic(vic);
    falsound.setBuffer(fal);
    soundbonM.setBuffer(bufM);
    soundbonB.setBuffer(bufB);
    soundvic.setBuffer(vic);

    sf::CircleShape rcircle(5.f);
    sf::Texture smile("images/smile.png");
    rcircle.setTexture(&smile);
    rcircle.setPosition({ 507, 33 });
    rcircle.scale({ 5, 5 });
  
    sf::Texture DistPanel;
    if (!DistPanel.loadFromFile("images/Dist.png"))
    {
        cerr << "Failed to load images/Dist.png" << endl;
        return 3;
    }
    sf::RectangleShape GameDistPanel(sf::Vector2f(1280, 113));
    GameDistPanel.setTexture(&DistPanel);
    GameDistPanel.setPosition(sf::Vector2f(0, 0));

    sf::Texture textureField;
    if (!textureField.loadFromFile("images/Kira.png"))
    {
        cerr << "Failed to load images/Kira.png" << endl;
        return 4;
    }
    sf::RectangleShape gamingBackground(sf::Vector2f(1280, 720));
    gamingBackground.setTexture(&textureField);

    sf::RectangleShape gamingBackground2(sf::Vector2f(1280, 720));
    gamingBackground2.setTexture(&textureField);
    gamingBackground2.setPosition(sf::Vector2f(1280, 0));

    int pusk = 0;
    double tmpfull = 0;
    int full = 100;

    sf::Font GameFont("fonts/Gotic.otf");
    sf::Text text_full(GameFont), plusfull(GameFont), text_pause(GameFont), end_game(GameFont);

    text_full.setFillColor(sf::Color::Green);
    text_full.setCharacterSize(30);
    text_full.setPosition({1070, 20});

    plusfull.setFillColor(sf::Color::Green);
    plusfull.setCharacterSize(25);

    end_game.setFillColor(sf::Color::Red);
    end_game.setCharacterSize(100);
    end_game.setString(L"Конец игры");
    end_game.setPosition({ 300, 333 });

    text_pause.setFillColor(sf::Color::Magenta);
    text_pause.setCharacterSize(50);
    text_pause.setString(L"П А У З А");
    text_pause.setPosition({ 500, 333 });

    bool GamePause = false;

    bool GameOver = false;
    sf::Vector2f pos;
    sf::Clock clock, clockAnim, clockAnimMeteor, clockAnimText;
    float time, timePasha, timeKira, timeMeteor;

    sf::Vector2f moveRec;
    sf::Texture pasha;
    if (!pasha.loadFromFile("images/Pasha.png"))
    {
        cerr << "Failed to load images/Pasha.png" << endl;
        return 5;
    }
    sf::RectangleShape pashok(sf::Vector2f(50, 60));
    pashok.setTexture(&pasha);
    pashok.setPosition(sf::Vector2f(80, 380));

    sf::Texture textBstu("images/bstu.png");
    sf::RectangleShape bstu(sf::Vector2f(250, 300));
    bstu.setTexture(&textBstu);
    bstu.setPosition(sf::Vector2f(485, 25));
    bstu.scale({0.25, 0.25});

    sf::Texture textBsr("images/bsr.png");
    sf::RectangleShape bsr(sf::Vector2f(200, 300));
    bsr.setTexture(&textBsr);
    bsr.setPosition(sf::Vector2f(930, 25));
    bsr.scale({ 0.25, 0.25 });

    sf::Texture belod("images/beloded.png");
    sf::RectangleShape bel(sf::Vector2f(900, 600));
    bel.setTexture(&belod);
    bel.setPosition({190, 60});
    bel.scale({1, 1 });

    FrameAnim DestructAnim;
    DestructAnim.Frame = 0; // Индекс по arrDestrX
    DestructAnim.Frame1 = 0; // Индекс по arrDestrY

    int arrAnim[4]{ 54, 143, 231, 326 };
    int Frame = 4, stepAnim = -1;

    int arrDestrX[5]{ 0, 160, 320, 470, 630 };
    int arrDestrY[4]{ 20, 240, 465, 685 };
    int DestrX = 0, DestrY = 0;

    sf::Texture pashokTexture;
    if (!pashokTexture.loadFromFile("images/fire.png"))
    {
        cerr << "Failed to load images/fire.png" << endl;
        return 6;
    }
    sf::Sprite pashokSprite(pashokTexture);
    pashokSprite.setTextureRect(sf::IntRect({ 0, 54 }, { 165, 70 }));

    sf::Texture texdest;
    if (!texdest.loadFromFile("images/destr.png"))
    {
        cerr << "Failed to load images/destr.png" << endl;
        return 7;
    }
    sf::Sprite destruction(texdest);
    destruction.setTextureRect(sf::IntRect({ 0, 20 }, { 135, 175 }));
    destruction.scale({ 1, 1 });

    Meteor meteor[15];
    int nmeteor = 15;

    Full canister("images/js.png", 100, 100);

    while (window.isOpen())
    {
        time = clock.getElapsedTime().asMicroseconds();
        timeKira = time / 6000;
        timeMeteor = time / 3000;
        timePasha = time / 2000;
        clock.restart();

        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyEvent->scancode)
                {
                case sf::Keyboard::Scancode::Tab:
                {
                    GamePause = !GamePause;
                    break;
                }
                case sf::Keyboard::Scancode::Escape:
                {
                    window.close();
                    break;
                }
                case sf::Keyboard::Scancode::M:
                {
                    mus = !mus;
                    if (mus)
                    {
                        gameMusic.play();
                    }
                    else
                    {
                        gameMusic.pause();
                    }
                    break;
                }
                case sf::Keyboard::Scancode::W:
                {
                    if (full != 0)
                    {
                        moveRec.y = -0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                case sf::Keyboard::Scancode::S:
                {
                    if (full != 0)
                    {
                        moveRec.y = 0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                case sf::Keyboard::Scancode::D:
                {
                    if (full != 0)
                    {
                        moveRec.x = 0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                case sf::Keyboard::Scancode::A:
                {
                    if (full != 0)
                    {
                        moveRec.x = -0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                case sf::Keyboard::Scancode::Numpad8:
                {
                    if (full != 0)
                    {
                        moveRec.y = -0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                case sf::Keyboard::Scancode::Numpad5:
                {
                    if (full != 0)
                    {
                        moveRec.y = 0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                case sf::Keyboard::Scancode::Numpad6:
                {
                    if (full != 0)
                    {
                        moveRec.x = 0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                case sf::Keyboard::Scancode::Numpad4:
                {
                    if (full != 0)
                    {
                        moveRec.x = -0.5 * timePasha;
                        full--;
                    }
                    break;
                }
                default:
                    break;
                }
            }
            else if (const auto* keyEvent = event->getIf<sf::Event::KeyReleased>())
            {
                switch (keyEvent->scancode)
                {
                case sf::Keyboard::Scancode::W:
                {
                    moveRec.y = 0;
                    break;
                }
                case sf::Keyboard::Scancode::S:
                {
                    moveRec.y = 0;
                    break;
                }
                case sf::Keyboard::Scancode::D:
                {
                    moveRec.x = 0;
                    break;
                }
                case sf::Keyboard::Scancode::A:
                {
                    moveRec.x = 0;
                    break;
                }
                case sf::Keyboard::Scancode::Numpad8:
                {
                    moveRec.y = 0;
                    break;
                }
                case sf::Keyboard::Scancode::Numpad5:
                {
                    moveRec.y = 0;
                    break;
                }
                case sf::Keyboard::Scancode::Numpad6:
                {
                    moveRec.x = 0;
                    break;
                }
                case sf::Keyboard::Scancode::Numpad4:
                {
                    moveRec.x = 0;
                    break;
                }
                default:
                    break;
                }
            }
        }
        if (!GamePause) {

            if (rcircle.getPosition().x <= 950) {
                if (GameOver)
                {
                    if (clockAnimMeteor.getElapsedTime() > sf::milliseconds(100))
                    {
                        clockAnimMeteor.restart();
                        DestructAnim.Frame++;
                        if (DestructAnim.Frame >= 5)
                        {
                            DestructAnim.Frame = 0;
                            DestructAnim.Frame1++;
                        }
                        if (DestructAnim.Frame1 >= 4)
                        {
                            GameOver = false;
                            pashok.setPosition(sf::Vector2f(80, 380));
                            for (int i = 0; i < nmeteor; i++)
                            {
                                meteor[i].restart();
                            }
                            canister.restart();
                            rcircle.setPosition({ 495, 33 });
                            DestructAnim.Frame = 0;
                            DestructAnim.Frame1 = 0;
                            full = 100;
                            DestrX = 0;
                            DestrY = 0;
                            destruction.setTextureRect(sf::IntRect({ arrDestrX[0], arrDestrY[0] }, { 135, 175 }));
                        }
                        else
                        {
                            destruction.setTextureRect(sf::IntRect({ arrDestrX[DestructAnim.Frame], arrDestrY[DestructAnim.Frame1] }, { 135, 175 }));
                        }
                    }
                }
                else
                {
                    if (clockAnim.getElapsedTime() > sf::milliseconds(150))
                    {
                        clockAnim.restart();
                        Frame += stepAnim;
                        pashokSprite.setTextureRect(sf::IntRect({ 0, arrAnim[Frame] }, { 165, 70 }));
                        if (Frame == 0) stepAnim = 1;
                        if (Frame == 2) stepAnim = -1;
                    }
                    pashokSprite.setPosition(sf::Vector2f(pashok.getPosition().x - 107, pashok.getPosition().y - 3));

                    if (clockAnimMeteor.getElapsedTime() > sf::milliseconds(80))
                    {
                        clockAnimMeteor.restart();
                        rcircle.move({ 0.5, 0 });
                    }

                    if (clockAnimText.getElapsedTime() > sf::milliseconds(50))
                    {
                        clockAnimText.restart();
                        if (pusk > 0)
                        {
                            pusk--;
                            plusfull.move({ 0, -1 });
                        }
                    }

                    gamingBackground.move({ -0.2f * timeKira, 0 });
                    pos = gamingBackground.getPosition();
                    if (pos.x < -1280)
                    {
                        gamingBackground.setPosition({ 1280, pos.y });
                    }
                    gamingBackground2.move({ -0.2f * timeKira, 0 });
                    pos = gamingBackground2.getPosition();
                    if (pos.x < -1280)
                    {
                        gamingBackground2.setPosition({ 1280, pos.y });
                    }
                    pashaMove(pashok, moveRec);

                    for (int i = 0; i < nmeteor; i++)
                    {
                        if (meteor[i].newBorn)
                        {
                            Correct(canister, i, meteor, nmeteor);
                        }
                        meteor[i].move(timeMeteor);
                        if (meteor[i].collision(pashok.getGlobalBounds()))
                        {
                            falsound.play();
                            GameOver = true;
                            destruction.setPosition({ pashok.getPosition().x, pashok.getPosition().y });
                            DestructAnim.Frame = 0;
                            DestructAnim.Frame1 = 0;
                            DestrX = 0;
                            DestrY = 0;
                            destruction.setTextureRect(sf::IntRect({ arrDestrX[0], arrDestrY[0] }, { 135, 175 }));
                            break;
                        }
                    }

                    if (canister.newBorn)
                    {
                        CorrectFull(canister, meteor, nmeteor);
                    }

                    canister.move(timeMeteor);

                    if (canister.collision(pashok.getGlobalBounds()))
                    {
                        tmpfull = 10 + rand() % 90;
                        full += tmpfull;
                        if (tmpfull > 50)
                        {
                            soundbonB.play();
                        }
                        else
                        {
                            soundbonM.play();
                        }
                        plusfull.setString(IntToStr(tmpfull));
                        plusfull.setPosition({ canister.getPosBonus().x, canister.getPosBonus().y });
                        pusk = 40;
                        canister.restart();
                    }

                    if (full >= 100) text_full.setFillColor(sf::Color::Green);
                    if (full < 100 && full >= 50) text_full.setFillColor(sf::Color::Yellow);
                    if (full < 50) text_full.setFillColor(sf::Color::Red);
                    text_full.setString(IntToStr(full) + L" тонн");
                }


                window.clear();
                window.draw(gamingBackground2);
                window.draw(gamingBackground);
                window.draw(GameDistPanel);
                window.draw(pashokSprite);
                if (!GameOver)
                {
                    window.draw(pashok);
                }
                for (int i = 0; i < nmeteor; i++)
                {
                    meteor[i].draw(window);
                }
                if (GameOver)
                {
                    window.draw(destruction);
                }
                canister.draw(window);
                window.draw(text_full);
                window.draw(rcircle);
                window.draw(bstu);
                window.draw(bsr);
                if (pusk > 0) window.draw(plusfull);
                window.display();
                if (rcircle.getPosition().x > 950)
                {
                    gameMusic.stop();
                    soundvic.play();
                }
            }
            else {
                window.clear();
                window.draw(gamingBackground2);
                window.draw(gamingBackground);
                window.draw(GameDistPanel);
                window.draw(text_full);
                window.draw(rcircle);
                window.draw(bstu);
                window.draw(bsr);
                window.draw(bel);
                window.draw(end_game);
                window.display();
                if (clockAnimText.getElapsedTime() > seconds(20))
                {
                    window.close();
                }
            }
        }
        else
        {
            window.draw(text_pause);
            window.display();
        }
    }
    
    return 0;
}