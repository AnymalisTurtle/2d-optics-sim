#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vector.cpp"
#include "Interactable.cpp"
#include "Util.cpp"


#ifndef POLYGON
class Polygon: public Interactable{
    private:
    Line *lines = 0;
    const char *type = 0;
    int linecount = 0;
    Interactable* last_element = 0;
    double refraction_index = 1.2;
    SurfaceProperty *sp;


    public:
    Polygon(Vector points[], int point_count, Interactable* last, double (*reflect)(double) = &SurfaceProperty::stdReflect, double (*refract)(double) = &SurfaceProperty::stdRefract, sf::Color color = sf::Color::White){
        // std::cout<<"--------------\ncreating polygon"<<std::endl;
        linecount = point_count;
        lines = new Line [linecount];
        this->last_element = last;
        Vector p1;
        Vector p2;
        for(int i = 0; i < linecount-1; i++){
            p1 = points[i];
            p2 = points[i+1];
            // std::cout<<"Drawing line from ("<<p1.x<<", "<<p1.y<<") to ("<<p2.x<<", "<<p2.y<<")"<<std::endl;
            lines[i] = Line(p1, p2);
            lines[i].set_color(color);
        }
        // std::cout<<"Drawing line from ("<<p2.x<<", "<<p2.y<<") to ("<<points[0].x<<", "<<points[0].y<<")"<<std::endl;
        lines[linecount-1] = Line(p2, points[0]);
        lines[linecount-1].set_color(color);

        this->sp = new SurfaceProperty(reflect, refract);
    };

    ~Polygon(){
        delete this->lines;
        delete this->sp;
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

    void set_color(sf::Color color){
        for(int i = 0; i < linecount; i++){
            lines[i].set_color(color);
        }
    };

    void draw(sf::RenderWindow &window){
        for(int i = 0; i < linecount; i++){
            lines[i].draw_as_primitive(window);
        }
    };

    SurfaceProperty* get_SurfaceProperty(){
        return this->sp;
    }

    double get_refraction_index(){
        return refraction_index;
    }

};
#define POLYGON
#endif