#include <string>

#include "Vector.cpp"

#ifndef EMITTER
class Emitter{
    private:
    std::string type;

    public:
    Emitter(){

    }

    virtual void move(Vector position, double angle) = 0;
    virtual Vector getPosition() = 0;
    virtual double getAngle() = 0;
    virtual Emitter * getLast() = 0;
    virtual void setLast(Emitter*) = 0;
    virtual void draw(sf::RenderWindow&) = 0;
    virtual void remove() = 0;
    virtual std::string getType() = 0;
    virtual int getRaycount() = 0;
    virtual void setRaycount(int) = 0;
    virtual double getWidth() = 0;
    virtual void setWidth(double) = 0;
};
#define EMITTER
#endif