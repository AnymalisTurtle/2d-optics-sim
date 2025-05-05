#include <SFML/Graphics.hpp>

#include "basic_objects\Vector.cpp"
#include "basic_objects\Line.cpp"
#include "basic_objects\Util.cpp"
#include "basic_objects\Wall.cpp"
#include "basic_objects\PointSource.cpp"


int main()
{

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Get refracted", sf::Style::Default, sf::State::Windowed, settings);


    Vector a(310, 400);
    Vector b(350, 600);
    Vector c(650, 530);
    Wall middle(
        Vector(500,0),
        Vector(500, 1000),
        0
    );
    Wall bottom(
        Vector(0,800),
        Vector(500, 950),
        &middle
    );

 


    Vector angled = a.Vector_angle_length(PI*2*113.199/360, 200);

    Line line1(a, b);
    Wall l1(a, b, &bottom);
    Line line2(b, c);
    Wall l2(b, c, &l1);
    Line line3(c, a);
    Wall l3(c, a, &l2);

    // Line angleline(b, angled+b);

    Line normal1 = line1.get_normal();
    Line normal2 = line2.get_normal();
    Line normal3 = line3.get_normal();

    line1.set_color(sf::Color::Red, sf::Color::Cyan);
    line2.set_color(sf::Color::Cyan, sf::Color::Green);
    line3.set_color(sf::Color::Green, sf::Color::Red);
    // angleline.set_color(sf::Color::Magenta, sf::Color::Magenta);


    PointSource ps(
        Vector(100, 100),
        30,
        (Interactable*) &l3
    );
    PointSource ps2(
        Vector(700, 500),
        30,
        (Interactable*) &l3
    );

    double dy =0;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        ps2 = PointSource(
            Vector(600+150*std::cos(dy), 500+50*std::sin(dy)),
            30,
            (Interactable*) &l3,
            dy/5
        );

        window.clear();
        // window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
        // window.draw(normal.data(), normal.size(), sf::PrimitiveType::Lines);
        line1.draw_as_primitive(window);
        line2.draw_as_primitive(window);
        line3.draw_as_primitive(window);
        normal1.draw_as_primitive(window);
        normal2.draw_as_primitive(window);
        normal3.draw_as_primitive(window);
        // angleline.draw_as_primitive(window);
        middle.draw(window);
        bottom.draw(window);
        ps.draw(window);
        ps2.draw(window);
        window.display();
        dy+=0.0001;
    }
}