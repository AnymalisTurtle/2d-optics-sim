
#include "Vector.cpp"

#ifndef EMITTER
class Emitter{
    private:

    public:
    Emitter(){

    }

    virtual void move(Vector position, double angle) = 0;
    virtual Vector getPosition() = 0;
    virtual Emitter * getLast() = 0;
    virtual void draw(sf::RenderWindow&) = 0;
};
#define EMITTER
#endif