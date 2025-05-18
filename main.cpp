#include <SFML/Graphics.hpp>

#include "basic_objects\Vector.cpp"
#include "basic_objects\Line.cpp"
#include "basic_objects\Util.cpp"
#include "basic_objects\Wall.cpp"
#include "basic_objects\PointSource.cpp"
#include "basic_objects\Polygon.cpp"


int main()
{

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Get refracted", sf::Style::Default, sf::State::Windowed, settings);


    Vector a(310, 400);
    Vector b(350, 600);
    Vector c(650, 530);
    Wall middle(
        Vector(500, 950),
        Vector(1000, 1000),
        0
    );
    Wall bottom(
        Vector(0,800),
        Vector(500, 950),
        &middle
    );

    Vector triPoints[] = {a,b,c};
    Polygon tri(triPoints, 3, &bottom, 0.4, 0.6, sf::Color(200, 200, 255));

    // Vector octPoints[] = {
    //     Vector(600,800),
    //     Vector(700,900),
    //     Vector(800,900),
    //     Vector(900,800),
    //     Vector(900,700),
    //     Vector(800,600),
    //     Vector(700,600),
    //     Vector(600,700)     
    // };
    // Polygon oct(octPoints, 8, &tri, 1, 0, sf::Color::Magenta);
 


    // Vector angled = a.Vector_angle_length(PI*2*113.199/360, 200);

    // Line line1(a, b);
    // Wall l1(a, b, &bottom);
    // Line line2(b, c);
    // Wall l2(b, c, &l1);
    // Line line3(c, a);
    // Wall l3(c, a, &l2);

    // Line angleline(b, angled+b);

    // Line normal1 = line1.get_normal();
    // Line normal2 = line2.get_normal();
    // Line normal3 = line3.get_normal();

    // line1.set_color(sf::Color::Red, sf::Color::Cyan);
    // line2.set_color(sf::Color::Cyan, sf::Color::Green);
    // line3.set_color(sf::Color::Green, sf::Color::Red);
    // angleline.set_color(sf::Color::Magenta, sf::Color::Magenta);

    int source_x=250;
    int source_y=520;
    PointSource ps(
        Vector(400, 500),
        30,
        (Interactable*) &tri
    );
    PointSource ps2(
        Vector(source_x, source_y),
        5,
        (Interactable*) &tri
    );

    double dy =0;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                    {
                        // std::cout << "the right button was pressed" << std::endl;
                        // std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                        // std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
                        source_x = mouseButtonPressed->position.x;
                        source_y = mouseButtonPressed->position.y;
                    }
                }
        }
        
        // ps2 = PointSource(
        //     Vector(450+160*std::cos(dy), 600+150*std::sin(dy)),
        //     20,
        //     (Interactable*) &oct,
        //     std::sin(dy/10)*2*PI
        // );
        ps2 = PointSource(
            Vector(source_x, source_y),
            40,
            (Interactable*) &tri,
            std::sin(dy/10)*2*PI
        );

        window.clear();

/*#####################################################
~~~~~~~~~~~~~~~~~~~~DRAWING SOURCES~~~~~~~~~~~~~~~~~~~~
#####################################################*/
       // ps.draw(window);
        ps2.draw(window);

/*#####################################################
~~~~~~~~~~~~~~~~~~~~DRAWING SHAPES~~~~~~~~~~~~~~~~~~~~~
#####################################################*/
        // window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
        // window.draw(normal.data(), normal.size(), sf::PrimitiveType::Lines);
        // line1.draw_as_primitive(window);
        // line2.draw_as_primitive(window);
        // line3.draw_as_primitive(window);
        // normal1.draw_as_primitive(window);
        // normal2.draw_as_primitive(window);
        // normal3.draw_as_primitive(window);
        // angleline.draw_as_primitive(window);
        
        middle.draw(window);
        bottom.draw(window);
        tri.draw(window);
        // oct.draw(window);
        window.display();
        dy+=0.00002;
    }
}