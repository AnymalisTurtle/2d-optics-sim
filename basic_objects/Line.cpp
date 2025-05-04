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
    };
    Line(float start_x, float start_y, float end_x, float end_y){
        this->p1 = Vector(start_x, start_y);
        this->p2 = Vector(end_x, end_y);
    };

    Line get_normal(float length = 30){
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
    }

    void draw_as_primitive(sf::RenderWindow &window){
        std::array line = line_from_vec(p1, p2);
        line[0].color = c1;
        line[1].color = c2;
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    }
};
#define LINE 1
#endif