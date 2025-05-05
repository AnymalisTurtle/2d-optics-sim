#include <SFML/Graphics.hpp>

#include "Emitter.cpp"
#include "Line.cpp"
#include "Ray.cpp"

class PointSource: public Emitter{
    private:
    Vector origin;
    int ray_count;
    double ray_length;
    Ray * rays = 0;

    public:
    PointSource(Vector origin, int number_of_rays, Interactable * obj, int obj_count, double length_of_rays = 500){
        this->origin = origin;
        this->ray_count = number_of_rays;
        this->ray_length = length_of_rays;
        rays = new Ray [ray_count];

        for (int i=0; i<ray_count; i++){
            Vector v = origin.Vector_angle_length(PI*2*i/ray_count, 1);
            Ray r(origin, v);
            r.trace(obj, obj_count);
            rays[i] = r;
            // std::cout<<"added ray to array"<<std::endl;
        }
    };

    void draw(sf::RenderWindow &window){
        for (int i=0; i<ray_count; i++){
            rays[i].draw(window);
        }
    };
};