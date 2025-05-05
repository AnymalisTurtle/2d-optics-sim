#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vector.cpp"
#include "Interactable.cpp"

class Wall: public Interactable{
    private:
    Line *lines = 0;
    const char *type = 0;
    int linecount = 1;
    sf::Color col1;
    sf::Color col2;
    Interactable* last_element = 0;

    public:
    Wall(Vector p1, Vector p2, Interactable* last, const char* type ="absorb", sf::Color color = sf::Color::White){
        lines = new Line [1];
        lines[0].set_points(p1, p2);
        this->type = type;
        this->col1 = color;
        this->col2 = color;
        this->last_element = last;
    };

    Interactable* get_last_element(){
        return last_element;
    }

    int get_linecount(){
        return linecount;
    };

    Line * get_line(int index){
        // std::cout<<"retrieveing line"<<std::endl;
        return &lines[index];
    }

    size_t get_size(){
        // std::cout<<"retrieveing size"<<std::endl;
        return sizeof(*this);
    }

    void set_color(sf::Color start_color, sf::Color end_color){
        this->col1 = start_color;
        this->col2 = end_color;
    };
    void set_color(sf::Color color){
        this->col1 = color;
        this->col2 = color;
    };

    void draw(sf::RenderWindow &window){
        lines->set_color(col1, col2);
        lines->draw_as_primitive(window);
    }


};

/*Interactable:
    private:
    Line * lines;
    int vertex_count;
    char* type;

    public:
    Interactable(int number_of_vertives, char* interact_type = "boundary"){
        this->lines = (Line*) malloc(sizeof(Line)*number_of_vertives);
        this->vertex_count = number_of_vertives;
        this->type = interact_type;
    };

    Line *get_line(int index){
        return lines + index*sizeof(Line); 
    };
    int get_linecount(){
        return vertex_count;
    };
    char* get_type(){
        return type;
    };
    size_t get_size(){
        return sizeof(this);
    }
*/