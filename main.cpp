#include <SFML/Graphics.hpp>

#include "basic_objects\vector.cpp"

int main()
{

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!", sf::Style::Default, sf::State::Windowed, settings);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    vector a(10, 10);
    vector b(200, 100);
    std::array line = line_from_vec(a, b);

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