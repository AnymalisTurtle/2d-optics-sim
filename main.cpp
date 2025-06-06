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

//Function declarations 
Emitter * getClosestEmitter(Emitter *, Vector);
void drawEmitters(Emitter *, sf::RenderWindow&);
void drawInteractables(Interactable *, sf::RenderWindow&);
void freeMem(Emitter *, Interactable *);

int main()
{
    //SFML window setup
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Get refracted", sf::Style::Default, sf::State::Windowed, settings);
    //fonts for UI
    sf::Font dotMatrix("media/fonts/DOTMATRI.ttf");
    sf::Font sevSeg("media/fonts/digital-7.ttf");
    sf::Text selection(sevSeg);
    sf::Text tooltip(sevSeg);

    // ** passed to all constructors: points to * which points to entry point(/object) of linked list 
    //the adress of ** is fixed; if the last element/entry point changes, change the * that ** points to -> all objects have the updated * by dereferencing **
    /*EXAMPLE
    1)create Interactable A;  (*lastInteractable : &A)
    2)create PointSource PS; (receives Interactable as argument)
    3)enter while loop: PS uses *lastInteractable (=&A) for ray intersection
    4)dynamically create Interactable B; (constructor changes *lastInteractable to &B) [not currently implemented :\]
    5)PS still uses the same lastInteractable, but it now dereferences to &B
    */
    Interactable ** lastInteractable = new Interactable*;
    *lastInteractable = 0;
    Emitter ** lastEmitter = new Emitter*;
    *lastEmitter = 0;

  
    //Exemplary setup of lenses and emitters:
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


    std::cout<<"\ncreating sources...\n";
    int source_x=250;
    int source_y=520;
    double source_angle = 0;
    double source_raycount = 5;
    double source_size = 0;
    std::string source_type ="";
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

    bool moveWithMouse = false; //flag shows if source is selected and to be effected by mouse movements
    bool editingSource = false; //flag shows if edit mode is enabled

    bool alt=false; bool ctrl=false; bool shift=false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if(editingSource){ //update modifiers when in edit mode
                    alt = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt);
                    ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
                    shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
                }

            if (event->is<sf::Event::Closed>())
                {
                // freeMem(*lastEmitter, *lastInteractable);
                window.close();
                }


            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    if (!editingSource){
                        moveWithMouse = !moveWithMouse; //enables/disables the active source following the cursor
                        source_x = mouseButtonPressed->position.x; //jump source to cursor, otherwise: left-click apparently doesn't do anything until mous is moved
                        source_y = mouseButtonPressed->position.y;
                        activeSource = getClosestEmitter(*lastEmitter, Vector(source_x, source_y)); //find the source closest to cursor
                        source_angle = activeSource->getAngle(); //"reset" angle change; prevent sudden rotation of source upon selection
                    }
                    
                }
                if (mouseButtonPressed->button == sf::Mouse::Button::Right){
                    //pointsource constructor automatically handles adding to the linke list
                    if(moveWithMouse){
                        activeSource->remove(); //handles removal from linked list and deletion of object
                        activeSource = 0; //nullptr for memory saftey
                        moveWithMouse = false; //exit move mode, as no source is selected anymore
                    } else if(editingSource){

                    } else {
                        //when not in the move mode, a new source should be created, otherwise the current source should be removed
                        new PointSource(Vector(mouseButtonPressed->position.x, mouseButtonPressed->position.y), 30, lastInteractable, lastEmitter);
                    }
                }
            }
            if (const auto * mouseMoved = event->getIf<sf::Event::MouseMoved>()){
                //only necessary when moving a source
                if(moveWithMouse){    
                    source_x = mouseMoved->position.x;
                    source_y = mouseMoved->position.y;
                }
            }
            if (const auto * mouseWheeled = event->getIf<sf::Event::MouseWheelScrolled>()){
                //only necessary when moving a source
                if(moveWithMouse){
                    source_angle += mouseWheeled->delta / 100; // factor 1/100 arbitrary
                } else 
                if(editingSource){
                    if(ctrl){ //change raycount
                        source_raycount += mouseWheeled->delta;
                        source_raycount = (source_raycount>0 ? source_raycount : 1);
                        activeSource->setRaycount(source_raycount);
                    } else 
                    if (shift){
                        if(source_type=="ParallelSource"){
                            source_size -= mouseWheeled->delta * 10;
                            activeSource->setWidth(source_size);
                        }
                    } else {
                        source_angle += mouseWheeled->delta / 100;
                    }
                }
            }

            if (const auto * keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if(moveWithMouse && activeSource!= 0){
                    if (keyPressed->code == sf::Keyboard::Key::E){
                        //enter edit mode for active source
                        editingSource = true;
                        moveWithMouse = false;
                        source_raycount = activeSource->getRaycount();
                        source_type = activeSource->getType();
                        if(source_type=="ParallelSource"){
                            source_size = activeSource->getWidth();
                        }
                    }
                }
                else if (editingSource){
                    if (keyPressed->code == sf::Keyboard::Key::Enter){
                        moveWithMouse = false;
                        editingSource = false;
                        activeSource = 0;
                    } else if (keyPressed->code == sf::Keyboard::Key::Tab){
                        if (ctrl) {
                            //change source type
                            if (source_type == "ParallelSource"){
                                activeSource->remove();
                                activeSource = new PointSource(Vector(source_x,source_y),source_raycount, lastInteractable, lastEmitter,source_angle);
                                source_type = "PointSource";
                            } else if (source_type == "PointSource"){
                                activeSource->remove();
                                if (source_size == 0) source_size = 10;
                                activeSource = new ParallelSource(Vector(source_x,source_y), source_raycount, source_size, lastInteractable, lastEmitter, source_angle);
                                source_type = "ParallelSource";
                            }
                        }
                    }
                }
            }
        }
        



        window.clear();

/*#####################################################
~~~~~~~~~~~~~~~~~~~~DRAWING SOURCES~~~~~~~~~~~~~~~~~~~~
#####################################################*/        
        //update the position of the current source
        if(moveWithMouse && activeSource!=0){
            activeSource->move(Vector(
                source_x,
                source_y
            ), source_angle);
        } else if (editingSource && activeSource != 0){
            activeSource->move(activeSource->getPosition(), source_angle);
        }

        drawEmitters(*lastEmitter, window);

/*#####################################################
~~~~~~~~~~~~~~~~~~~~DRAWING SHAPES~~~~~~~~~~~~~~~~~~~~~
#####################################################*/

        drawInteractables(*lastInteractable, window);

/*#####################################################
~~~~~~~~~~~~~~~~~~~~DRAWING TEXT~~~~~~~~~~~~~~~~~~~~~~~
#####################################################*/
        //adjusting text based on current selection/mode
        if(moveWithMouse){
            std::stringstream ttText;
            ttText << activeSource->getType() << " selected\n(" << activeSource << ")";
            selection.setString(ttText.str());
            tooltip.setString("left-click: set in place | scroll: rotate | right-click: remove | E: edit source");
        } else if (editingSource){
            std::stringstream ttText;
            ttText << activeSource->getType() << " selected\n(" << activeSource << ")";
            selection.setString(ttText.str());
            if (source_type == "ParallelSource"){
                tooltip.setString("scroll: rotate | ctrl+scroll: raycount | shift+scroll: width | ctrl+tab: change source-type | Enter: Exit Edit Menu");
            } else {
                tooltip.setString("scroll: rotate | ctrl+scroll: raycount | ctrl+tab: change source-type | Enter: Exit Edit Menu");
            }
        } else {
            selection.setString("-/-");
            tooltip.setString("left-click: select | right-click: create new source");
        }


        selection.setCharacterSize(24);
        //alligning the text on the bottom: window height - text height - margin
        selection.setPosition(sf::Vector2f(5, window.getSize().y -selection.getLocalBounds().size.y -selection.getCharacterSize()/2 -5));
        selection.setFillColor(sf::Color::Magenta);
        tooltip.setCharacterSize(24);
        //alligning the text on the right edge: window_width - text_width - margin
        tooltip.setPosition(sf::Vector2f(window.getSize().x - tooltip.getLocalBounds().size.x -5, 
                                        window.getSize().y -tooltip.getLocalBounds().size.y -tooltip.getCharacterSize()/2 -5));
        tooltip.setFillColor(sf::Color::Cyan);

        //splitting the tooltip strings into two lines, if both strings are too close (replace first " | " with "\n")
        if(tooltip.getLocalBounds().size.x + selection.getLocalBounds().size.x + 20 > window.getSize().x){
            std::string helper = tooltip.getString();
            int spacePos = helper.find(" | ", helper.size()/2-1);
            helper = helper.replace(spacePos, 3, "\n");
            tooltip.setString(helper);
            tooltip.setPosition(sf::Vector2f(window.getSize().x - tooltip.getLocalBounds().size.x -5, 
                                            window.getSize().y -tooltip.getLocalBounds().size.y -tooltip.getCharacterSize()/2 -5));
        }


        window.draw(selection);
        window.draw(tooltip);
        
        window.display();
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
