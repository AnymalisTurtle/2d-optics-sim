#include <SFML/Graphics.hpp>

#include "basic_objects\Vector.cpp"
#include "basic_objects\Line.cpp"
#include "basic_objects\Util.cpp"
#include "basic_objects\Wall.cpp"
#include "basic_objects\PointSource.cpp"
#include "basic_objects\Polygon.cpp"
#include "basic_objects\Lens.cpp"
#include "basic_objects\Emitter.cpp"
#include "basic_objects\ParallelSource.cpp"
#include <sstream>

Emitter * getClosestEmitter(Emitter *, Vector);
void drawEmitters(Emitter *, sf::RenderWindow&);
void drawInteractables(Interactable *, sf::RenderWindow&);
void freeMem(Emitter *, Interactable *);

int main()
{

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Get refracted", sf::Style::Default, sf::State::Windowed, settings);

    sf::Font dotMatrix("media/fonts/DOTMATRI.ttf");
    sf::Font sevSeg("media/fonts/digital-7.ttf");
    sf::Text tooltip(sevSeg);

    Interactable ** lastInteractable = new Interactable*;
    *lastInteractable = 0;
    Emitter ** lastEmitter = new Emitter*;
    *lastEmitter = 0;

    Vector a(110, 200);
    Vector b(510, 800);
    Vector c(950, 730);
    // Wall middle(
    //     Vector(500, 950),
    //     Vector(1000, 1000),
    //     0
    // );
    // Wall bottom(
    //     Vector(0,800),
    //     Vector(500, 950),
    //     &middle
    // );

    // Vector triPoints[] = {a,b,c};
    // Polygon tri(triPoints, 3, &bottom, &SurfaceProperty::stdReflect, &SurfaceProperty::stdRefract, sf::Color(200, 200, 255));
    std::cout<<"creating lenses...\n";
    Lens lens(300, 300+20+2, 500, 50, 20, lastInteractable, 0, Lens::concaveParabolic);
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;
    Lens lens2(300, 300, 500, 50, 20, lastInteractable);
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;
    Lens lens3(300, 400+20+2, 500, 50, 20, lastInteractable, 0, Lens::concaveParabolic);
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;
    Lens lens4(300, 400, 500, 50, 20, lastInteractable);
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;
    Lens lens5(300, 600-20-2, 500, 50, 20, lastInteractable, 0, Lens::concaveParabolic);
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;
    Lens lens6(300, 600, 500, 50, 20, lastInteractable);
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;

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

    std::cout<<"\ncreating sources...\n";
    int source_x=250;
    int source_y=520;
    double source_angle = 0;
    Emitter *activeSource = 0;
    PointSource * ps = new PointSource(
        Vector(400, 500),
        30,
        lastInteractable,
        lastEmitter
    );
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;
    std::cout<<"lastEmitter: "<<lastEmitter<<" *lastEmitter: "<<*lastEmitter<<std::endl;
    PointSource * ps2 = new PointSource(
        Vector(source_x, source_y),
        100,
        lastInteractable,
        lastEmitter,
        source_angle,
        500, 
        sf::Color(230, 230, 255)
    );
    std::cout<<"lastInteractable: "<<lastInteractable<<" *lastInteractable: "<<*lastInteractable<<std::endl;
    std::cout<<"lastEmitter: "<<lastEmitter<<" *lastEmitter: "<<*lastEmitter<<std::endl;
    ParallelSource * parallel = new ParallelSource(
        Vector(100, 600),
        30,
        50,
        lastInteractable,
        lastEmitter
    );

    double dy =0;
    bool moveWithMouse = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                {
                freeMem(*lastEmitter, *lastInteractable);
                window.close();
                }


            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    // std::cout << "the right button was pressed" << std::endl;
                    // std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                    // std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
                    moveWithMouse = !moveWithMouse;
                    source_x = mouseButtonPressed->position.x;
                    source_y = mouseButtonPressed->position.y;
                    activeSource = getClosestEmitter(*lastEmitter, Vector(source_x, source_y));
                }
                if (mouseButtonPressed->button == sf::Mouse::Button::Right){
                    if (!moveWithMouse) new PointSource(Vector(mouseButtonPressed->position.x, mouseButtonPressed->position.y), 30, lastInteractable, lastEmitter);
                    else{
                        activeSource->remove();
                        activeSource = 0;
                        moveWithMouse = false;
                    }
                }
            }
            if (const auto * mouseMoved = event->getIf<sf::Event::MouseMoved>()){
                if(moveWithMouse){    
                    source_x = mouseMoved->position.x;
                    source_y = mouseMoved->position.y;
                }
            }
            if (const auto * mouseWheeled = event->getIf<sf::Event::MouseWheelScrolled>()){
                if(moveWithMouse){
                    source_angle += mouseWheeled->delta / 100;
                }
            }
        }
        



        window.clear();

/*#####################################################
~~~~~~~~~~~~~~~~~~~~DRAWING SOURCES~~~~~~~~~~~~~~~~~~~~
#####################################################*/
        
        drawEmitters(*lastEmitter, window);

        if(moveWithMouse && activeSource!=0){
            activeSource->move(Vector(
                source_x,
                source_y
            ), source_angle);
        }

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
        
        // middle.draw(window);
        // bottom.draw(window);
        // tri.draw(window);
        drawInteractables(*lastInteractable, window);

/*#####################################################
~~~~~~~~~~~~~~~~~~~~DRAWING TEXT~~~~~~~~~~~~~~~~~~~~~~~
#####################################################*/
        if(moveWithMouse){
            std::stringstream ttText;
            ttText << "Source selected (" << activeSource << ")";
            tooltip.setString(ttText.str());
        } else {
            tooltip.setString("-/-");
        }

        tooltip.setCharacterSize(24);
        tooltip.setFillColor(sf::Color::Magenta);
        window.draw(tooltip);
        
        window.display();
        // dy+=0.00002;
    }
}

Emitter * getClosestEmitter(Emitter * last_emitter, Vector point){
    double min_distance = -1;
    Emitter * closest = 0;
    while (last_emitter!=0){
        std::cout<<"checking distance of Emitter "<<last_emitter<<std::endl;
        Vector vec = last_emitter->getPosition();
        double distance = (point-vec).length();
        if (distance < min_distance || min_distance < 0){
            min_distance = distance;
            closest = last_emitter;
        }
        last_emitter = last_emitter->getLast();
    }
    std::cout<<"closest Emitter found to be: "<<closest<<std::endl;
    return closest;
}

void drawEmitters(Emitter* last_em, sf::RenderWindow &window){
    while (last_em != 0){
        last_em->draw(window);
        last_em = last_em->getLast();
    }
}
void drawInteractables(Interactable* last_Inter, sf::RenderWindow &window){
    while (last_Inter != 0){
        last_Inter->draw(window);
        last_Inter = last_Inter->get_last_element();
    }
}

void freeMem(Emitter* last_em, Interactable* last_Inter){
    while (last_em != 0){
        Emitter * prev_em = last_em;
        last_em = last_em->getLast();
        delete prev_em;
    }
    while (last_Inter != 0){
        Interactable * prev_Inter = last_Inter;
        last_Inter = last_Inter->get_last_element();
        delete prev_Inter;
    }
}
