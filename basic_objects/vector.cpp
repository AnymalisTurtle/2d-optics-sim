#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


class Vector{
    public:
    float x;
    float y;
    float z;
    bool is2d;


    Vector(float x_init, float y_init, float z_init){
        this->x = x_init;
        this->y = y_init;
        this->z = z_init;
        this->is2d = false;
    }
    //2d vector implementation
    Vector(float x_init, float y_init){
        this->x = x_init;
        this->y = y_init;
        this->is2d = true;
    }
    Vector(Vector start, Vector end){
        if (start.is2d && end.is2d){
            this->is2d = true;
        }else{
            this->is2d = false;
        }

        this->x = end.x - start.x;
        this->y = end.y - start.y;
        this->z = end.z - start.z;
    }
    
    float length(){
        return sqrt( pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) );
    }

    void unit(){
        float le = this->length();
        if (le != 0){
            this->x /= le;
            this->y /= le;
            this->z /= le;
        }else{
            std::cerr << "cannot unit zero-vector!";
        }
    }

    // vector-chains which define a body should always run ccw; normals should point outward
    // therefore the normal can be calculated for each segment of the vector chain individually
    // so far only working with 2d; z has to be zero
    Vector get_normal_2d(){
        if (this->is2d){
            std::cerr << "Function not implemented for 3d vectors";
        }
        Vector normal(this->y, -this->x, 0);
        normal.unit();
        return normal;
    }
};

// #creates a drawable line from vector objects for start and end points
std::array<sf::Vertex, 2> line_from_vec(Vector p1, Vector p2){
    std::array line = 
    {
        sf::Vertex{sf::Vector2f(p1.x, p1.y)},
        sf::Vertex{sf::Vector2f(p2.x, p2.y)} 
    };
    return line;
};