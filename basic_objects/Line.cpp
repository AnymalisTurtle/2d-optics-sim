#include <SFML/Graphics.hpp>

#include "Vector.cpp"
#include "util.cpp"

#ifndef LINE
class Line{
    private:
    Vector p1;
    Vector p2;
    sf::Color c1;
    sf::Color c2;

    public:
    Line(Vector start, Vector end){
        this->p1 = start;
        this->p2 = end;
        this->c1 = sf::Color::White;
        this->c2 = sf::Color::White;
    };
    Line(double start_x, double start_y, double end_x, double end_y){
        this->p1 = Vector(start_x, start_y);
        this->p2 = Vector(end_x, end_y);
        this->c1 = sf::Color::White;
        this->c2 = sf::Color::White;
    };
    Line(){
        p1 = Vector(0,0);
        p2 = Vector(1,1);
    };

    Line get_normal(double length = 50){
        // a + (b-a)*0.5
        Vector midpoint = p1 + (p2-p1)*0.5;
        Vector n = (p2-p1).get_normal_2d();
        Line normal(midpoint, midpoint+n*length);
        normal.set_color(sf::Color::White, sf::Color::White);
        return normal;
    };

    void set_color(sf::Color start_color, sf::Color end_color){
        this->c1 = start_color;
        this->c2 = end_color;
    };
    void set_color(sf::Color color){
        this->c1 = color;
        this->c2 = color;
    };

    void set_points(Vector p1, Vector p2){
        this->p1 = p1;
        this->p2 = p2;
    }

    void draw_as_primitive(sf::RenderWindow &window){
        std::array line = line_from_vec(p1, p2);
        line[0].color = c1;
        line[1].color = c2;
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    };

    Vector get_a(){//startpoint
        return p1;
    };
    Vector get_b(){//direction s.t. a+1*b = p2
        return (p2-p1);
    };
};
#define LINE
#endif