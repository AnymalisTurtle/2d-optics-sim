#include <SFML/Graphics.hpp>

#include "Emitter.cpp"
#include "Line.cpp"
#include "Ray.cpp"

class PointSource: public Emitter{
    private:
    Vector origin;
    double angle;
    int ray_count;
    double ray_length;
    Ray * rays = 0;
    sf::Color color;

    public:
    PointSource(Vector origin, int number_of_rays, Interactable * obj, double angle = 0, double length_of_rays = 500){
        this->origin = origin;
        this->angle = angle;
        this->ray_count = number_of_rays;
        this->ray_length = length_of_rays;
        this->color = sf::Color::White;
        rays = new Ray [ray_count];

        

        for (int i=0; i<this->ray_count; i++){
            Vector v = this->origin.Vector_angle_length(PI*2*i/this->ray_count + this->angle, 1);
            Ray r(this->origin, v, 0, 0, this->color, this->color);
            r.trace(obj);
            this->rays[i] = r;
            // std::cout<<"added ray to array"<<std::endl;
        }
    };

    void draw(sf::RenderWindow &window){
        for (int i=0; i<ray_count; i++){
            rays[i].draw(window);
        }
    };
};