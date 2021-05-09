#include "splash.h"

void SplashScreen::show(sf::RenderWindow& renderWindow)
{
    sf::Texture splashTx;
    if (!splashTx.loadFromFile("res/splash.jpg"))
    {
        return;
    }

    sf::Sprite splashSpr(splashTx);

    renderWindow.draw(splashSpr);
    renderWindow.display();

    sf::Event event;
    while (true)
    {
        if (renderWindow.pollEvent(event) && (
            event.type == sf::Event::EventType::KeyPressed ||
            event.type == sf::Event::EventType::MouseButtonPressed ||
            event.type == sf::Event::EventType::Closed
            )
            ) {
            return;
        }
    }
}
