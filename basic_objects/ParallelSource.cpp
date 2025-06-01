#include <SFML/Graphics.hpp>

#include "Emitter.cpp"
#include "Line.cpp"
#include "Ray.cpp"

#ifndef PARALLELSOURCE
class ParallelSource : public Emitter{
    private:
    Vector origin;
    double width;
    double angle;
    int ray_count;
    double ray_length;
    Ray * rays = 0;
    sf::Color color;
    Interactable ** obj_ptr;
    Emitter * last_em = 0;

    void reTrace(){
        // std::cout<<"retracing with *obj: "<<*(this->obj_ptr)<<std::endl;
        if (! this->rays == 0) delete this->rays;
        this->rays = new Ray [this->ray_count];

        Vector v = Vector::Vector_angle_length(this->angle, 1);
        Vector lineDir = v.get_normal_2d();
        for (int i=-0; i<this->ray_count; i++){
            //lineDir gives direction of startPoint spread
            Vector rayOrigin = origin + lineDir * ((double)i - ray_count/2)*(this->width/ray_count);          
            Ray r(rayOrigin, v, 0, 0, this->color, this->color);
            r.trace(*(this->obj_ptr));
            this->rays[i] = r;
        }
    }


    public:
    ParallelSource(Vector origin, int number_of_rays, double width, Interactable ** obj, Emitter ** em, double angle = 0, double length_of_rays = 500, sf::Color col = sf::Color(255, 255, 255)){
        this->origin = origin;
        this->angle = angle;
        this->width = width;
        this->ray_count = number_of_rays;
        this->ray_length = length_of_rays;
        this->color = col;
        this->obj_ptr = obj;
        this->last_em = *em;
        *em = this;
        std::cout<<"creating PLS ("<<this<<") with last_emitter: "<<this->last_em<<std::endl;
        // std::cout<<"nnumber of rays: "<<number_of_rays<<", ray_count: "<<this->ray_count<<std::endl;
        this->reTrace();
        // std::cout<<"finished ps constructor ("<< this <<")\n";
    };

    ~ParallelSource(){
        // std::cout<<"ps destructor called("<< this <<")"<<std::endl;
        delete this->rays;
    };

    void move(Vector position, double angle){
        this->origin = position;
        this->angle = angle;
        this->reTrace();
    }

    void draw(sf::RenderWindow &window){
        // std::cout<<"drawing ps("<<this<<")\n";
        if (!this->rays == 0){
            for (int i=0; i<this->ray_count; i++){
                // std::cout<<"drawing ray #"<<i<<std::endl;;
                this->rays[i].draw(window);
            }
        }
    }

    Vector getPosition(){
        return origin;
    }

    Emitter * getLast(){
        return last_em;
    }
};
#define PARALLELSOURCE
#endif