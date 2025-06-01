#include <SFML/Graphics.hpp>

#include "Emitter.cpp"
#include "Line.cpp"
#include "Ray.cpp"

#ifndef POINTSOURCE
class PointSource : public Emitter{
    private:
    Vector origin;
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

        for (int i=0; i<this->ray_count; i++){
            // std::cout<<"creating ray with i="<<i<<std::endl;
            Vector v = this->origin.Vector_angle_length(PI*2*i/this->ray_count + this->angle, 1);
            Ray r(this->origin, v, 0, 0, this->color, this->color);
            // std::cout<<"tracing ray"<<std::endl;
            r.trace(*(this->obj_ptr));
            // std::cout<<"adding ray to array..."<<std::endl;
            this->rays[i] = r;
        }
    }


    public:
    PointSource(Vector origin, int number_of_rays, Interactable ** obj, Emitter ** em, double angle = 0, double length_of_rays = 500, sf::Color col = sf::Color(255, 255, 255)){
        this->origin = origin;
        this->angle = angle;
        this->ray_count = number_of_rays;
        this->ray_length = length_of_rays;
        this->color = col;
        this->obj_ptr = obj;
        this->last_em = *em;
        *em = this;
        std::cout<<"creating PS ("<<this<<") with last_emitter: "<<this->last_em<<std::endl;
        // std::cout<<"nnumber of rays: "<<number_of_rays<<", ray_count: "<<this->ray_count<<std::endl;
        this->reTrace();
        // std::cout<<"finished ps constructor ("<< this <<")\n";
    };

    ~PointSource(){
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
#define POINTSOURCE
#endif