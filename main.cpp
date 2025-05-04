#include <SFML/Graphics.hpp>

int main()
{

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!", sf::Style::Default, sf::State::Windowed, settings);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::array line = 
    {
        sf::Vertex{sf::Vector2f(10.f, 10.f)},
        sf::Vertex{sf::Vector2f(100.f, 100.f)} 
    };

    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Cyan;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
        window.display();
    }
}